#include "../include/utils.hpp"
#include "math.h"

void cross_product(vector& result,vector& a, vector& b){
    result(0)=a(1)*b(2)-a(2)*b(2);
    result(1)=a(2)*b(0)-a(0)*b(2);
    result(2)=a(0)*b(1)-a(1)*b(0);
}

void normalize(vector& a) {
    double t = sqrt(a(0)^2 + a(1)^2 + a(2)^2);
    a(0) = a(0) / t;
    a(1) = a(1) / t;
    a(2) = a(2) / t;
}

vector cross_product_2(vector& a, vector& b) {
    vector result(3);
    result(0)=a(1)*b(2)-a(2)*b(2);
    result(1)=a(2)*b(0)-a(0)*b(2);
    result(2)=a(0)*b(1)-a(1)*b(0);
    return result;
}

double dot_product(vector& a, vector& b) {
    return sqrt(a(0) * b(0) + a(1) * b(1) + a(2) * b(2));
}