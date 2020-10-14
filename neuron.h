#pragma once

class Neuron
{
private:
    int inputSize;
    float* inputWeights;
    float bias;

public:
    Neuron(int inputSize);
    ~Neuron();

    float activate(float* inputs);
    void train(float* inputs, float target, float learningRate);

private:
    float activationFunction(float value);

};
