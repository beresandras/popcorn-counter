#include <Servo.h>
#include <PDM.h>
#include "LedMatrix.h"
#include "NeuralNetwork.h"

// States transition times (ms)
int state = 0;
const int startTime = 2000;
int stopTime;


// Servo
const int servoPin = 9;
const int servoCenter = 96;
const int servoAmplitude = 24;
Servo servo;

// Neural network parameters
const int downsample = 4;
const int inputSize = 1000;
const int outputSize = 800;
NeuralNetwork *nn;

float currentPops;
float numPops = 0.0f;
float const maxPops = 150.0f;

// Sound recording
const int numChannels = 1;
const long sampleRate = 16000;
const int gain = 20;
const int bufferSize = 4000; // inputSize * downsample
const int warmupTime = 5000; // ms

int16_t rawSoundBuffer[bufferSize];
float soundBuffer1[inputSize];
float soundBuffer2[inputSize];

float* pFrontBuffer = soundBuffer1; // gets written
float* pBackBuffer = soundBuffer2; // gets processed

volatile uint16_t bufferIndex = 0;
volatile bool processData = false;
volatile bool dataError = false;

// Display
const int chipSelectPin = 10;
LedMatrix ledMatrix = LedMatrix(chipSelectPin);

void setup() {
  Serial.begin(500000);
  
  servo.attach(servoPin);
  servo.write(servoCenter);

  ledMatrix.begin();

  PDM.onReceive(onReceiveSound);
  PDM.setGain(gain);
  
  if (!PDM.begin(numChannels, sampleRate)) {
    Serial.println("Error: microphone initialization failed");
    while(1);
  }
  
  nn = new NeuralNetwork();
}

void loop() {
  if (dataError) {
    Serial.println("Warning: could not process all data in time");
  }

  // check if the buffers have been swapped -> sound should be processed
  if (processData) {
    currentPops = 3.0f * nn->predict(pBackBuffer, inputSize, outputSize);
    // after startup the microphone readings are not zero-centered
    if (millis() > warmupTime) {
      numPops += currentPops;
    }
    Serial.println(currentPops);
    processData = false;
  }

  switch (state) {
    case 0: // startup
      if (millis() > startTime) {
        servo.write(servoCenter - servoAmplitude);
        state++;
      }
      break;
    case 1: // microwave started
      if (millis() > startTime + 500) {
        servo.write(servoCenter);
        state++;
      }
      break;
    case 2:
      if (numPops >= maxPops) {
        stopTime = millis() + 500;
        servo.write(servoCenter + servoAmplitude);
        state++;
      }
      break;
    case 3:
      if (millis() > stopTime) {
        displayState(int(numPops), 0.0f);
        servo.write(servoCenter);
        state++;
      }
      break;
  }

  if (state < 4) {
    displayState(int(numPops), numPops / maxPops);
  }
}

void onReceiveSound(void) {
  float* pTempBuffer;
  int numNewSamples = PDM.available() / 2; // 2 bytes per sample
  int numFreeSpace = bufferSize - bufferIndex;
  
  PDM.read(rawSoundBuffer, 2 * numNewSamples);
  
  // check if front buffer is full
  if (numFreeSpace < numNewSamples) {  
    // check if previous data was sent
    if (processData) {
      dataError = true;
    }

    // write what fits
    for (int i = 0; i < numFreeSpace; i++) {
      pFrontBuffer[(bufferIndex + i) / downsample] += float(rawSoundBuffer[i]) / downsample;
    }
    numNewSamples -= numFreeSpace;
      
    // swap buffers
    pTempBuffer = pBackBuffer;
    pBackBuffer = pFrontBuffer;
    pFrontBuffer = pTempBuffer;

    // reset buffer index
    bufferIndex = 0;
    processData = true;
  }
  
  for (int i = 0; i < numNewSamples; i++) {
      pFrontBuffer[(bufferIndex + i) / downsample] += float(rawSoundBuffer[i]) / downsample;
  }
  bufferIndex += numNewSamples;
}

void displayState(int count, float progress) {
    // time
    int seconds = 0;
    if (millis() > startTime) {
      seconds = (millis() - startTime) / 1000;
    }
    ledMatrix.displayDigit(seconds / 600, 0, 0);
    ledMatrix.displayDigit(seconds / 60, 0, 4);
    ledMatrix.displayPixel(1, 8);
    ledMatrix.displayPixel(3, 8);
    ledMatrix.displayDigit((seconds % 60) / 10, 0, 10);
    ledMatrix.displayDigit((seconds % 60), 0, 14);

    // count
    ledMatrix.displayDigit(count / 100, 0, 21);
    ledMatrix.displayDigit(count / 10, 0, 25);
    ledMatrix.displayDigit(count, 0, 29);

    // progress
    ledMatrix.displayProgress(progress, 6, 2);
    ledMatrix.show();
}
