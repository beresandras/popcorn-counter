#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <SPI.h>

class LedMatrix {
private:
    // register adresses
    static const uint16_t REG_DIGIT_X = 0x01;
    static const uint16_t REG_DECODE = 0x09;
    static const uint16_t REG_INTENSITY = 0x0A;
    static const uint16_t REG_SCAN_LIMIT = 0x0B;
    static const uint16_t REG_ENABLE = 0x0C;  // shutdown register
    static const uint16_t REG_TEST = 0x0F;

    // digit blueprints
    // drawn left-right mirrored at https://gurgleapps.com/tools/matrix
    static constexpr uint8_t digits[10][8] = {
        {0x07, 0x05, 0x05, 0x05, 0x07, 0x00, 0x00, 0x00},
        {0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00},
        {0x07, 0x04, 0x07, 0x01, 0x07, 0x00, 0x00, 0x00},
        {0x07, 0x04, 0x07, 0x04, 0x07, 0x00, 0x00, 0x00},
        {0x05, 0x05, 0x07, 0x04, 0x04, 0x00, 0x00, 0x00},
        {0x07, 0x01, 0x07, 0x04, 0x07, 0x00, 0x00, 0x00},
        {0x07, 0x01, 0x07, 0x05, 0x07, 0x00, 0x00, 0x00},
        {0x07, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00},
        {0x07, 0x05, 0x07, 0x05, 0x07, 0x00, 0x00, 0x00},
        {0x07, 0x05, 0x07, 0x04, 0x07, 0x00, 0x00, 0x00},
    };

    static const int numSegments = 4;
    const int chipSelectPin;
    const SPISettings spiSettings;

    uint8_t displayBuffer[numSegments][8];

public:
    LedMatrix(const int chipSelectPin) : chipSelectPin(chipSelectPin), spiSettings(5000000, MSBFIRST, SPI_MODE0) {}

    void begin(void);
    void sendCommand(const uint8_t address, uint8_t data);
    void displayPixel(const int rowOffset, const int columnOffset);
    void displayDigit(const int digit, const int rowOffset, const int columnOffset);
    void displayProgress(const float progress, const int rowOffset, const int height);
    void show(void);
};

#endif
