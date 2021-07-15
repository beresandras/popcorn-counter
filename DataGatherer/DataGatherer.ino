#include <PDM.h>

// microphone settings
const int numChannels = 1;
const long sampleRate = 16000;
const int gain = 20;

// sound buffers
const uint16_t bufferSize = 16000; // gets filled in ca. 1 second

uint16_t soundBuffer1[bufferSize];
uint16_t soundBuffer2[bufferSize];

uint16_t* pFrontSoundBuffer = soundBuffer1;
uint16_t* pBackSoundBuffer = soundBuffer2;

volatile uint16_t frontBufferIndex = 0;
volatile uint16_t backBufferIndex = 0;
volatile uint32_t globalOffset = 0;

const float reactionTime = 0.2f; // in seconds
const uint32_t reactionOffset = reactionTime * sampleRate;

const float repetitionTime = 0.01f; // min. time between two button presses in seconds
const uint32_t repetitionDiff = repetitionTime * sampleRate;

// pop counting
const int buttonPin = 2;

uint32_t popArray[256];

volatile uint16_t popArrayIndex = 0;
volatile uint16_t popArrayIndex = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  PDM.onReceive(onReceiveSound);
  PDM.setGain(gain);
  
  if (!PDM.begin(numChannels, sampleRate)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }

  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), onButtonPress, FALLING);
}

void loop() {
  if (backBufferIndex != 0) {
    // buffers have been swapped
    Serial.println("Buffer swap");
    Serial.println(popArrayIndex);
    // send pop array size
    // send back buffer size
    // send pop array
    // send back buffer
    backBufferIndex = 0;
  }
}

void onReceiveSound() {
  uint16_t* pTempBuffer;
  
  int numNewSamples = PDM.available() / 2;
  if (bufferSize - frontBufferIndex <= numNewSamples) {
    // front buffer is full -> swap buffers
    pTempBuffer = pBackBuffer;
    pBackBuffer = pFrontBuffer;
    pFrontBuffer = pTempBuffer;

    globalOffset += frontBufferIndex;
    backBufferIndex = frontBufferIndex;
    frontBufferIndex = 0;
  }
  PDM.read(pFrontBuffer + frontBufferIndex, 2 * numNewSamples);
  frontBufferIndex += numNewSamples;
}

void onButtonPress() {
  // check value
  uint32_t newPopIndex = globalOffset + frontBufferIndex - reactionOffset;
  uint32_t oldPopIndex = 
  
  if (popArrayIndex == 0) { 
    popArray[(popArrayIndex - 1) % 256]
  }
  if (
  popArray[popArrayIndex % 256] = 
  popArrayIndex++;
}
