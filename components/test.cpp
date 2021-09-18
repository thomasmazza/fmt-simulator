//
// Created by stce on 18.09.21.
//

#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include "component.hpp"

using namespace boost::numeric::ublas;

int main(int argc, char *argv[]){
    vector<double> vec(argv[1]);
    component::Component<double> testComp = component::Component(&vec);
    std::cout << "Result Test " << testComp.getPos() << std::endl;
    return 0;
};