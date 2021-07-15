#include <PDM.h>

// microphone settings
const int numChannels = 1;
const long sampleRate = 16000;
const int gain = 20;

// sound buffers
const uint16_t bufferSize = 16000; // gets filled in ca. 4 seconds

uint16_t soundBuffer1[bufferSize];
uint16_t soundBuffer2[bufferSize];

uint16_t* pFrontBuffer = soundBuffer1;
uint16_t* pBackBuffer = soundBuffer2;

volatile uint16_t frontBufferIndex = 0;
volatile uint16_t backBufferIndex = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  PDM.onReceive(onReceiveSound);
  PDM.setGain(gain);
  
  if (!PDM.begin(numChannels, sampleRate)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }
}

void loop() {
  if (backBufferIndex != 0) {
    // buffers have been swapped
    Serial.println("Buffer swap");
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

    backBufferIndex = frontBufferIndex;
    frontBufferIndex = 0;
  }
  PDM.read(pFrontBuffer + frontBufferIndex, 2 * numNewSamples);
  frontBufferIndex += numNewSamples;
}
