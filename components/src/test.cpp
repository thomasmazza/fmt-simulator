#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "component.hpp"
#include "filter.hpp"
#include "mirror.hpp"
#include "ellipticalMirror.hpp"

int main(int argc, char *argv[]){
    vector testVector (3);
    for( unsigned  i = 0; i < testVector.size(); i++){
        testVector(i) = i;
    }
    Filter filter1(testVector, testVector, 1,1);
    std::cout << filter1.getLowerLimit() << '\n';
    Component component1(testVector, testVector);
    vector test = component1.getPosition();
    std::cout << test << '\n';
    Mirror mirror1(testVector, testVector,testVector,testVector,testVector);
    EllipticalMirror(testVector, testVector, testVector, testVector,testVector, 1 ,1);

};