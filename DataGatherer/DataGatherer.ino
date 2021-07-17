#include <PDM.h>

// Constants
const int numChannels = 1;
const long sampleRate = 16000;
const int gain = 20;
const int buttonPin = 2;
const uint16_t bufferSize = 1 * sampleRate; // gets filled in ca. 1 second
const char endOfFrame[] = "end_of_frame";

// Sound recording

// 16-bit values: 2 bytes per sample
uint8_t soundBuffer1[2 * bufferSize];
uint8_t soundBuffer2[2 * bufferSize];

// 8-bit values: 1 byte per sample
uint8_t popBuffer1[bufferSize];
uint8_t popBuffer2[bufferSize];

uint8_t* pFrontSoundBuffer = soundBuffer1; // gets written
uint8_t* pBackSoundBuffer = soundBuffer2; // gets read

uint8_t* pFrontPopBuffer = popBuffer1; // gets written
uint8_t* pBackPopBuffer = popBuffer2; // gets read

volatile uint16_t frontBufferIndex = 0;
volatile uint16_t backBufferIndex = 0;

volatile bool dataError = false;

void setup() {
  Serial.begin(500000);
  while (!Serial);

  PDM.onReceive(onReceiveSound);
  PDM.setGain(gain);
  
  if (!PDM.begin(numChannels, sampleRate)) {
    Serial.println("Error: microphone initialization failed");
    while(1);
  }

  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), onButtonPress, FALLING);
}

void loop() {
  if (dataError) {
    Serial.println("Error: could not send all data in time");
    while(1);
  }

  // check if the buffers have been swapped -> new sound should be sent
  if (backBufferIndex != 0) {
    Serial.write(pBackSoundBuffer, 2 * backBufferIndex);
    Serial.write(pBackPopBuffer, backBufferIndex);
    Serial.write(endOfFrame, 12);
    
    backBufferIndex = 0;
  }
}

void onReceiveSound() {
  uint8_t* pTempBuffer;
  int numNewSamples = PDM.available() / 2; // 2 bytes per sample
  
  // check if front buffer is full
  if (bufferSize - frontBufferIndex <= numNewSamples) {  

    // check if previous data was sent
    if (backBufferIndex != 0) {
      dataError = true;
    }
      
    // swap sound buffers
    pTempBuffer = pBackSoundBuffer;
    pBackSoundBuffer = pFrontSoundBuffer;
    pFrontSoundBuffer = pTempBuffer;
    
    // swap pop buffers
    pTempBuffer = pBackPopBuffer;
    pBackPopBuffer = pFrontPopBuffer;
    pFrontPopBuffer = pTempBuffer;
    
    // swap indices
    backBufferIndex = frontBufferIndex;
    frontBufferIndex = 0;
  }
  PDM.read(pFrontSoundBuffer + 2 * frontBufferIndex, 2 * numNewSamples);
  memset(pFrontPopBuffer + frontBufferIndex, 0x00, numNewSamples);
  frontBufferIndex += numNewSamples;
}

void onButtonPress() {
  // check if we received any samples since startup
  if (frontBufferIndex > 0) {
    pFrontPopBuffer[frontBufferIndex - 1] = 0x01;
  }
}
