#include "neuron.h"
#include <random>
#include <iostream>

Neuron::Neuron(int inputSize)
    : inputSize(inputSize), bias(0)
{
    // initialize weights randomly
    inputWeights = new float[inputSize];
    for (int i = 0; i < inputSize; i++)
        inputWeights[i] = (float)(rand() % 20000) / 10000.0f - 1.0f;
}

Neuron::~Neuron()
{
    delete[] inputWeights;
}

float Neuron::activate(float* inputs)
{
    float output = 0;
    for (int i = 0; i < inputSize; i++)
        output += inputs[i] * inputWeights[i];
    return activationFunction(output) + bias;
}

float Neuron::activationFunction(float x)
{
    return 1.0f / (1.0f + exp(-x));
}

void Neuron::train(float* inputs, float target, float learningRate)
{
    float result = activate(inputs);
    float error = target - result;

    bias += error * learningRate;
    for (int i = 0; i < inputSize; i++)
        inputWeights[i] += error * inputs[i] * learningRate;
}
