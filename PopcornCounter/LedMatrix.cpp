#include "LedMatrix.h"

constexpr uint8_t LedMatrix::digits[10][8];

void LedMatrix::begin(void) {
    pinMode(chipSelectPin, OUTPUT);
    SPI.begin();

    sendCommand(REG_TEST, 0x00);
    sendCommand(REG_DECODE, 0x00);
    sendCommand(REG_INTENSITY, 0x00);
    sendCommand(REG_SCAN_LIMIT, 0x07);
    sendCommand(REG_ENABLE, 0x01);

    for (int row = 0; row < 8; row++) {
        for (int segment = 0; segment < numSegments; segment++) {
            displayBuffer[segment][row] = 0x00;
        }
    }
}

void LedMatrix::sendCommand(const uint8_t address, uint8_t data) {
    SPI.beginTransaction(spiSettings);
    digitalWrite(chipSelectPin, LOW);
    for (int segment = 0; segment < numSegments; segment++) {
        SPI.transfer(address);
        SPI.transfer(data);
    }
    digitalWrite(chipSelectPin, HIGH);
    SPI.endTransaction();
}

void LedMatrix::displayPixel(const int rowOffset, const int columnOffset) {
    int segment = (columnOffset / 8) % numSegments;
    displayBuffer[segment][rowOffset % 8] |= 0x01 << (columnOffset % 8);
}

void LedMatrix::displayDigit(const int digit, const int rowOffset, const int columnOffset) {
    int segment1 = (columnOffset / 8) % numSegments;
    int segment2 = ((columnOffset + 2) / 8) % numSegments;
    for (int row = rowOffset; row < 8; row++) {
        displayBuffer[segment1][row] |= digits[digit % 10][row - rowOffset] << (columnOffset % 8);
        displayBuffer[segment2][row] |= digits[digit % 10][row - rowOffset] >> (8 - columnOffset % 8);
    }
}

void LedMatrix::displayProgress(const float progress, const int rowOffset, const int height) {
    for (int row = rowOffset; row < 8; row++) {
        if (row < rowOffset + height) {
            int progressPixels = int(progress * numSegments * 8);
            for (int segment = 0; segment < numSegments; segment++) {
                if (progressPixels >= 8) {
                    displayBuffer[segment][row] |= 0xFF;
                    progressPixels -= 8;
                }
                else {
                    displayBuffer[segment][row] |= 0xFF >> (8 - progressPixels % 8);
                    progressPixels = 0;
                }
            }
        }
    }
}

void LedMatrix::show(void) {
    SPI.beginTransaction(spiSettings);
    // rows are from top to bottom
    for (int row = 0; row < 8; row++) {
        digitalWrite(chipSelectPin, LOW);
        // segments are from left to right, last segment is sent first
        for (int segment = numSegments - 1; segment >= 0; segment--) {
            SPI.transfer(REG_DIGIT_X + (7 - row));
            SPI.transfer(displayBuffer[segment][row]);
            displayBuffer[segment][row] = 0x00;
        }
        digitalWrite(chipSelectPin, HIGH);
    }
    SPI.endTransaction();
}
