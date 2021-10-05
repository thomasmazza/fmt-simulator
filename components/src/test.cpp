#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "lensOneSided.hpp"
#include "lens.hpp"
#include "component.hpp"
#include "mirror.hpp"
#include "../../photon/include/photon.hpp"
#include "utils.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

int main(int argc, char *argv[]) {
    vector testVector(3);
    vector testVector2(3);
    vector testVector3(3);
    vector testVector4(3);
    testVector2(0)=-1;
    testVector2(1)=0;
    testVector2(2)=0;

    testVector3(0)=-1;
    testVector3(1)=1;
    testVector3(2)=1;

    testVector4(0)=1;
    testVector4(1)=5;
    testVector4(2)=3;

    int sum1=0;
    for(int i=0; i<3; i++){
        sum1 += pow(testVector4[i], 2);
    }
    sum1=sqrt(sum1);
    for(int i=0; i<3; i++){
        testVector4[i] = testVector4[i]/sum1;
    }

    for (unsigned i = 0; i < testVector.size(); i++) {
        testVector(i) = 1;
    }
    std::cout<<testVector4<<std::endl;

    LensOneSided lens1(testVector, testVector2,1.5 ,30 ,80 ,5 ,true);
    Photon testPhoton(testVector3,testVector4, 600, 500);
    std::cout<<testPhoton.getDirection()<<std::endl;
    if (lens1.getOutDir(testPhoton) == true){
        std::cout<<testPhoton.getDirection()<<std::endl;
    }
};