//
// Created by stce on 18.09.21.
//

#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "component.hpp"

using namespace boost::numeric::ublas;

int main(int argc, char *argv[]){
    vector<double> vec(std::stoi(argv[1]));
    for(int i=0; i<vec.size(); i++) vec(i)=i;
    component::Component<double> testComp(vec);
    std::cout << "Test vector " << testComp.getPos() << std::endl;
    return 0;
};