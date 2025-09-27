#include <cmath>
#include <vector>
#include <algorithm>

double sigmoid(double a){
    return 1/(1+exp(-a));
}

double ddxSigmoid(double sigmoid){
    return sigmoid*(1-sigmoid);
}

double relu(double x){
    return std::max(0.0,x);
}

double ddxRelu(double x){
    return x >= 0? 1.0 : 0.0;
}

std::vector<double> vectSigmoid(std::vector<double> Input){

    std::vector<double>output;
    for(double i : Input){
        output.push_back(sigmoid(i));
    }
    return output;
}

std::vector<double> ddxVectSigmoid(std::vector<double> Input){

    std::vector<double>output;
    for(double i : Input){
        output.push_back(ddxSigmoid(i));
    }
    return output;
}

std::vector<double> vectReLU(std::vector<double> Input){
    std::vector<double> output;
    output.reserve(Input.size());
    for(double i : Input) {
        output.push_back(relu(i));
    }
    return output;
}

std::vector<double> ddxVectReLU(std::vector<double> Input){
    std::vector<double> output;
    output.reserve(Input.size()); // reserve space for efficiency
    for(double i : Input){
        output.push_back(ddxRelu(i));
    }
    return output;
}
