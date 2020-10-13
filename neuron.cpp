#include "neuron.h"
#include <random>
#include <iostream>

Neuron::Neuron(int inputSize)
    : inputSize(inputSize)
{
    // initialize weights randomly
    inputWeights = new float[inputSize];
    for (int i = 0; i < inputSize; i++)
        inputWeights[i] = (float)(rand() % 20000) / 10000.0f - 1.0f;
    // initialize bias randomly
    inputBias = new float[inputSize];
    for (int i = 0; i < inputSize; i++)
        inputBias[i] = 1.0f;

}

Neuron::~Neuron()
{
    delete[] inputWeights;
    delete[] inputBias;
}

float Neuron::activate(float* inputs)
{
    float output = 0;
    for (int i = 0; i < inputSize; i++)
        output += inputs[i] * inputWeights[i];
    return activationFunction(output);
}

float Neuron::activationFunction(float value)
{
    return value >= 0 ? 1.0f : -1.0f;
}

void Neuron::train(float* inputs, float target, float learningRate)
{
    float result = activate(inputs);
    float error = target - result;

    for (int i = 0; i < inputSize; i++)
        inputWeights[i] += error * inputs[i] * learningRate;
}
