#include "LedMatrix.h"

const int chipSelectPin = 10;
LedMatrix ledMatrix = LedMatrix(chipSelectPin);

void setup() {
    ledMatrix.begin();
}

void loop() {
    for (int16_t num = 0; num < 10000; num++) {
        displayState(num, 0.99f);
        delay(100);
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
