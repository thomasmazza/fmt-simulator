#include "operators.hpp"
#include <assert.h>

std::vector<double> operator+(const std::vector<double>& vector1, const std::vector<double>& vector2){
    assert(vector1.size()==vector2.size());
    std::vector<double> vector;
    for(unsigned int i = 0;i<vector1.size();i++){
        vector = vector1 + vector2;
    }
    return vector;
}

std::vector<double> operator-(const std::vector<double>& vector1, const std::vector<double>& vector2){
    assert(vector1.size()==vector2.size());
    std::vector<double> vector(vector1.size());
    for(unsigned int i = 0;i<vector1.size();i++){
        vector[i] = vector1[i] - vector2[i];
    }
    return vector;
}

std::vector<double> operator-(const std::vector<double>& _vector){
    std::vector<double> vector;
    for(unsigned int i = 0; i < _vector.size(); i++){
        vector[i] = -_vector[i];
    }
    return vector;
}

std::vector<double> operator*(const std::vector<double>& _vector, const double& scalar){
    std::vector<double> vector(_vector.size());
    for(unsigned int i =0; i<_vector.size();i++){
        vector[i] = scalar*_vector[i];
    }
    return vector;
}
std::vector<double> operator*(const double& scalar, const std::vector<double>& _vector){
    return _vector*scalar;
}

std::ostream& operator<<(std::ostream& os, const std::vector<double>& _vector){
    for( unsigned  int i = 0;i<_vector.size();i++){
        os << _vector[i] << "," ;
    }
    return os;
}