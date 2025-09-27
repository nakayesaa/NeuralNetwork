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


