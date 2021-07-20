#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <TensorFlowLite.h>

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

static const int tensorArenaSize = 20000;

namespace tflite {
    class MicroErrorReporter;
    class Model;
    template <unsigned int t>
    class MicroMutableOpResolver;
    class MicroInterpreter;
}  // namespace tflite

struct TfLiteTensor;

class NeuralNetwork {
private:
    tflite::MicroErrorReporter errorReporter;
    const tflite::Model* model;
    tflite::MicroMutableOpResolver<2> resolver;
    tflite::MicroInterpreter* interpreter;
    uint8_t tensorArena[tensorArenaSize];

    TfLiteTensor* input;
    TfLiteTensor* output;

public:
    NeuralNetwork();
    float predict(const float* pInputBuffer, const int inputSize, const int outputSize);
};

#endif
