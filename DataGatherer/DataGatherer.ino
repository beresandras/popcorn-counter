#include <PDM.h>

#include "LedMatrix.h"

// Sound recording
const int numChannels = 1;
const long sampleRate = 16000;
const int gain = 20;
const int buttonPin = 2;
const uint16_t bufferSize = 1 * sampleRate;  // gets filled in ca. 1 second
const char endOfFrame[] = "end_of_frame";
const unsigned long debounceTime = 100;  // button debouncing time in ms

// 16-bit values: 2 bytes per sample
uint8_t soundBuffer1[2 * bufferSize];
uint8_t soundBuffer2[2 * bufferSize];

// 8-bit values: 1 byte per sample
uint8_t popBuffer1[bufferSize];
uint8_t popBuffer2[bufferSize];

uint8_t* pFrontSoundBuffer = soundBuffer1;  // gets written
uint8_t* pBackSoundBuffer = soundBuffer2;   // gets read

uint8_t* pFrontPopBuffer = popBuffer1;  // gets written
uint8_t* pBackPopBuffer = popBuffer2;   // gets read

volatile uint16_t bufferIndex = 0;
volatile bool sendData = false;
volatile bool dataError = false;
volatile unsigned long lastButtonPressTime = 0;
volatile int numButtonPresses = 0;

// Display
const int chipSelectPin = 10;
LedMatrix ledMatrix = LedMatrix(chipSelectPin);

void setup() {
    Serial.begin(500000);
    while (!Serial);

    ledMatrix.begin();

    PDM.onReceive(onReceiveSound);
    PDM.setGain(gain);

    if (!PDM.begin(numChannels, sampleRate)) {
        Serial.println("Error: microphone initialization failed");
        while (1);
    }

    pinMode(buttonPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonPin), onButtonPress, FALLING);
}

void loop() {
    if (dataError) {
        Serial.println("Error: could not send all data in time");
        while (1);
    }

    // check if the buffers have been swapped -> new sound should be sent
    if (sendData) {
        Serial.write(pBackSoundBuffer, 2 * bufferSize);
        Serial.write(pBackPopBuffer, bufferSize);
        Serial.write(endOfFrame, 12);  // omitting the last '\0' on purpose

        sendData = false;
    }

    displayState(numButtonPresses, 0.0f);
}

void onReceiveSound(void) {
    uint8_t* pTempBuffer;
    int numNewSamples = PDM.available() / 2;  // 2 bytes per sample
    int numFreeSpace = bufferSize - bufferIndex;

    // check if front buffer is full
    if (numFreeSpace < numNewSamples) {
        // check if previous data was sent
        if (sendData) {
            dataError = true;
        }

        // write what fits
        PDM.read(pFrontSoundBuffer + 2 * bufferIndex, 2 * numFreeSpace);
        memset(pFrontPopBuffer + bufferIndex, 0x00, numFreeSpace);
        numNewSamples -= numFreeSpace;

        // swap sound buffers
        pTempBuffer = pBackSoundBuffer;
        pBackSoundBuffer = pFrontSoundBuffer;
        pFrontSoundBuffer = pTempBuffer;

        // swap pop buffers
        pTempBuffer = pBackPopBuffer;
        pBackPopBuffer = pFrontPopBuffer;
        pFrontPopBuffer = pTempBuffer;

        // reset buffer index
        bufferIndex = 0;
        sendData = true;
    }
    PDM.read(pFrontSoundBuffer + 2 * bufferIndex, 2 * numNewSamples);
    memset(pFrontPopBuffer + bufferIndex, 0x00, numNewSamples);
    bufferIndex += numNewSamples;
}

void onButtonPress(void) {
    unsigned long currentTime = millis();

    // buffer should not be empty + software button debouncing
    if (bufferIndex > 0 && currentTime - lastButtonPressTime > debounceTime) {
        pFrontPopBuffer[bufferIndex - 1] = 0x01;
        lastButtonPressTime = currentTime;
        numButtonPresses++;
    }
}

void displayState(int count, float progress) {
    // time
    int seconds = millis() / 1000;
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
