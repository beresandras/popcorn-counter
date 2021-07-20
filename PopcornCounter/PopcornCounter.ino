#include "NeuralNetwork.h"

NeuralNetwork *nn;
const int inputSize = 1000;
const int outputSize = 800;
float inputBuffer[inputSize];

void setup() {
  Serial.begin(115200);
  nn = new NeuralNetwork();
}

void loop() {
  for (int i = 0; i < inputSize; i++) {
    inputBuffer[i] = 10.0f;
  }
  float result = nn->predict(inputBuffer, inputSize, outputSize);
  Serial.println(result);
}
