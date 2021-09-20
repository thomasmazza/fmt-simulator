//
// Created by stce on 18.09.21.
//

#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "component.hpp"

using namespace boost::numeric::ublas;

int main(int argc, char *argv[]){
    int dim=std::stoi(argv[1]);
    vector<double> vec(dim);
    vector<double> normal(dim);
    for(int i=0; i<dim; i++) vec(i)=i;
    component::Component<double> testComp(vec,normal);
    std::cout << "Test vector " << testComp.getPos() << std::endl << "with dir " << testComp.getNormal() << std::endl;
    return 0;
};