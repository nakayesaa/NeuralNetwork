#include <algorithm>
#include "helper.cpp"
#include "activationmethod.cpp"

class Layer{
    public:
    std::vector<double> input;
    std::vector<double> output;
    virtual std::vector<double> forward(const std::vector<double> inputData) = 0;
    virtual std::vector<double> backward(const std::vector<double> error, double lr) = 0;
};

class Sigmoid : public Layer{
    public:
    virtual std::vector<double> forward(const std::vector<double> inputData) override{
        input = inputData;
        output = vectSigmoid(input);
        return output;
    }
    virtual std::vector<double> backward(const std::vector<double> error, double lr) override{
        std::vector<double> derivative = ddxVectSigmoid(input);
        std::vector<double> gradientInput;
        for(int i = 0; i<derivative.size();i++){
            gradientInput.push_back(derivative[i] * error[i]);
        }
        return gradientInput;
    }
};

class Relu : public Layer{
    public :
    virtual std::vector<double> forward(const std::vector<double> InputData)override{
        input = InputData;
        output = vectReLU(input);
        return output;
    }
    virtual std::vector<double> backward(const std::vector<double> error, double lr)override{
        std::vector<double> derivative = ddxVectReLU(input);
        std::vector<double> gradInput;
        for(int i = 0; i<derivative.size();i++){
            gradInput.push_back(derivative[i] * error[i]);
        }
        return gradInput;
    }
};

class Linear : public Layer{
    public : 
    int inputNeuron;
    int outputNeuron;
    std::vector<std::vector<double>> weight;
    std::vector<double> bias;

    Linear(int inputNumber, int ouputNumber){
        inputNeuron = inputNumber;
        outputNeuron = outputNeuron;
        weight = assingWeight(ouputNumber, inputNumber);
    }
    std::vector<double> forward(const std::vector<double> inputData) override{
        input = inputData;
        output.clear();
        for(int i = 0; i<outputNeuron;i++){
            output.push_back(dotProduct(weight[i], input) + bias[i]);
        }
        return output;
    }
    std::vector<double> backward(const std::vector<double> error, double lr) override{
        std::vector<double> inputError;
        std::vector<std::vector<double>> weightError;
        std::vector<double> biasError;
        std::vector<std::vector<double>> weightTranspose;

        weightTranspose = matrixTranspose(weight);
        biasError = error;

        for(int i = 0; i<weightTranspose.size();i++){
            inputError.push_back(dotProduct(weightTranspose[i],error));
        }
        for(int i = 0; i<error.size();i++){
            std::vector<double> row;
            for(int j = 0; j<input.size();i++){
                row.push_back(error[j] * input[i]);
            }
            weightError.push_back(row);
        }

        std::vector<double> newBias = elementWise(biasError, lr);
        bias = vectorSubs(bias,newBias);
        for(int i = 0; i<weightError.size();i++){
            std::vector<double> newWeight = elementWise(weightError[i],lr);
            weight[i] = vectorSubs(weight[i], newWeight);
        }
        return inputError;
    }
};

