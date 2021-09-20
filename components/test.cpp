//
// Created by stce on 18.09.21.
//

#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "filter.hpp"

using namespace boost::numeric::ublas;

int main(int argc, char *argv[]){
    int dim=std::stoi(argv[1]);
    vector<double> vec(dim);
    vector<double> normal(dim);
    for(int i=0; i<dim; i++) vec(i)=i;
    component::Filter<double> testFilter(vec,normal,250,750);
    int lambda=335;
    std::cout << "Test pos " << testFilter.getPos() << std::endl << "with dir " << testFilter.getNormal() << std::endl
    << lambda << " is in range of filter: " << testFilter.inRange(lambda) << std::endl;
    return 0;
};