#include <vector>
#include <math.h>
#include <cmath>
#include "helper.cpp"

double mseLoss(std::vector<double> Desired, std::vector<double> output){
    double sum = 0;
    for(int i = 0; i<Desired.size();i++){
        sum += pow(Desired[i] - output[i], 2.0);
    }
    double loss = sum/Desired.size();
    return loss;
}

std::vector<double> mseLossDerivative(std::vector<double> Desired, std::vector<double> Output){
    std::vector<double> error = vectorSubs(Desired,Output);
    std::vector<double> ddx = elementWise(error,2.0);
    return ddx;
}

