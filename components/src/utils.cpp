#include "../include/utils.hpp"

void cross_product(vector& result,vector& a, vector& b){
    result(0)=a(1)*b(2)-a(2)*b(2);
    result(1)=a(2)*b(0)-a(0)*b(2);
    result(2)=a(0)*b(1)-a(1)*b(0);
}