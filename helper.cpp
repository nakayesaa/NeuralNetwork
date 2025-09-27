#include <vector>
#include <iostream>
#include <random>
#include <functional>
#include <algorithm>
#include <chrono>

double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2){
    double result = 0;
    for(std::size_t i = 0; i<v1.size();i++){
        result+= v1[i] * v2[i];
    }
    return result;
}

std::vector<double> elementWise(std::vector<double> &vector, double scalar){
    for(int i = 0; i<vector.size();i++){
        vector[i] = vector[i] * scalar;
    }
    return vector;
}

std::vector<double> vectorSubs(std::vector<double> &vector1, std::vector<double> &vector2){
    std::vector<double> result;
    for(int i = 0; i<vector1.size();i++){
        result[i] = vector1[i] - vector2[i];
    }
    return result;
}

std::vector<std::vector<double>> matrixTranspose(std::vector<std::vector<double>> &m){
    std::vector<std::vector<double>> vectorTransform;
    int rows = m.size();
    int column = m[1].size();
    for(int i = 0; i<rows;i++){
        for(int j = 0; j<column;j++){
            vectorTransform[j][i] = m[i][j];
        }
    }
    return vectorTransform;
}

std::vector<std::vector<double>> assingWeight(int r, int c){

    std::random_device randNum;
    std::mt19937 gen(randNum() ^ std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution distNum(-1.0,1.0);


    std::vector<std::vector<double>> weight(r, std::vector<double>(c));
    for(int i = 0; i<r;i++){
        for(int j = 0; j<c;j++){
            weight[i][j] = distNum(gen);
        }
    }

    return weight;
}





