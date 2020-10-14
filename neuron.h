#pragma once

class Neuron
{
private:
    int inputSize;
    double* inputWeights;
    double bias;

public:
    Neuron(int inputSize);
    ~Neuron();

    double activate(double* inputs);
    void train(double* inputs, double target, double learningRate);

    double getLineY(double x);

private:
    double activationFunction(double value);

};
