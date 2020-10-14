#include "neuron.h"
#include <random>
#include <iostream>

Neuron::Neuron(int inputSize)
    : inputSize(inputSize), bias(0)
{
    // initialize weights randomly
    inputWeights = new double[inputSize];
    for (int i = 0; i < inputSize; i++)
        inputWeights[i] = (double)(rand() % 20000) / 10000.0 - 1.0;
}

Neuron::~Neuron()
{
    delete[] inputWeights;
}

double Neuron::activate(double* inputs)
{
    double output = 0;
    for (int i = 0; i < inputSize; i++)
        output += inputs[i] * inputWeights[i] + bias;
    return activationFunction(output);
}

double Neuron::activationFunction(double x)
{
    // return 1.0 / (1.0 + exp(-x)); // sigmoid
    // return x > 0 ? 1.0 : -1.0; // step
    return x;
}

void Neuron::train(double* inputs, double target, double learningRate)
{
    double result = activate(inputs);
    double error = target - result;

    bias += error * learningRate;
    for (int i = 0; i < inputSize; i++)
        inputWeights[i] += error * inputs[i] * learningRate;
}

// Calculate the Decision Boundary of a Single Perceptron - Visualizing Linear Separability
double Neuron::getLineY(double x)
{
    return (-(bias / inputWeights[1]) / (bias / inputWeights[0])) * x + (-bias / inputWeights[1]);
}
