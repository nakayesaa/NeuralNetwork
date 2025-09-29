#include <vector>
#include <memory>
#include <iostream>
#include "layer.cpp"
#include "lossFunction.cpp"

class neuralNetwork{
    public : 
    std::vector<std::unique_ptr<Layer>> layers;
    //a vector where each element is a smart pointer that hold one layer 
    
    void add(std::unique_ptr<Layer> layer){
        layers.push_back(std::move(layer));
    }

    std::vector<double> runs(std::vector<double> Input){
        return forwardPropagation(Input);
    }

    std::vector<double> forwardPropagation(const std::vector<double> input){
        std::vector<double> output = input;
        for(const auto &layer : layers){
            output = layer->forward(output);
        }
        return output;
    }

    std::vector<double> backwardPropagation(const std::vector<double> &error, double lr){
        std::vector<double> grad = error;
        for(auto i = layers.rbegin(); i!=layers.rend();i++){
            grad = (*i)->backward(grad,lr);
        }
    }

    void fit(std::vector<std::vector<double>> &input, std::vector<std::vector<double>> &lable, int epoch, double lr){
        for(int i = 0; i<epoch;++i){
            double totalLoss = 0;
            for(int j = 0; j<input.size();++j){
                std::vector<double> output = forwardPropagation(input[i]);
                double loss = mseLoss(lable[i], output);
                totalLoss += loss;

                std::vector<double> ddxLoss = mseLossDerivative(lable[i], output);
                backwardPropagation(ddxLoss, lr);
            }
            std::cout << "Epoch " << epoch + 1 << "/" << i << " - Loss: " << totalLoss / input.size() << std::endl;
        }
    }
};
