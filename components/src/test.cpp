#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "lensOneSided.hpp"
#include "lens.hpp"
#include "filter.hpp"
#include "lensTwoSided.hpp"
#include "mirrorElliptical.hpp"
#include "mirrorRectangle.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

int main(int argc, char *argv[]) {
    vector testVector(3);
    vector testVector2(3);
    vector testVector3(3);
    vector testVector4(3);
    vector testVector5(3);

    vector filterPos(3);
    vector filterDir(3);

    testVector2(0)=-1;
    testVector2(1)=0;
    testVector2(2)=0;

    testVector3(0)=-1;
    testVector3(1)=1;

    testVector3(2)=1;

    testVector4(0)=1;
    testVector4(1)=0;
    testVector4(2)=0;

    testVector5[0]=-1;
    testVector5[1]=0;
    testVector5[2]=1;

    filterPos(0)=0;
    filterPos(1)=1;
    filterPos(2)=1;

    filterDir(0)=-1;
    filterDir(1)=0;
    filterDir(2)=0;




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


    LensTwoSided lens2(testVector, testVector2,1.5 ,10 ,-30 ,30 ,5);
    Photon testPhoton(testVector3,testVector4, 600, 500);
    Filter filter(filterPos, filterDir, 450, 700);

    if (lens2.getOutDir(testPhoton) == true){
        std::cout<<"New direction: "<<testPhoton.getDirection()<<std::endl;
    }

    testVector[0] = 10;

    LensOneSided lens1(testVector, testVector2,1.5 ,20 ,21 ,5 ,false);

    if (lens1.getOutDir(testPhoton) == true){
        std::cout<<"New direction 2: "<<testPhoton.getDirection()<<std::endl;
    }

    //test mirror

    testVector[0] = 1;
    double Z=0;
    for(int i=0; i<3; i++){
        Z += pow(testVector5[i], 2);
    }
    Z=sqrt(Z);
    for(int i=0; i<3; i++){
        testVector5[i] = testVector5[i]/Z;
    }

    MirrorRectangle rec1(testVector, testVector5, 20, 20);
    Photon testPhoton2(testVector3,testVector4, 600, 0);
    Photon testPhoton3(testVector3,testVector4, 800, 0);
    vector trace = rec1.getPosition()-testPhoton2.getPosition();

    Z=0;
    for(int i=0; i<3; i++){
        Z += pow(trace[i], 2);
    }
    Z=sqrt(Z);
    for(int i=0; i<3; i++){
        trace[i] = trace[i]/Z;
    }

    if (rec1.getOutDir(testPhoton2,trace)){
        std::cout<<"New direction 3: "<<testPhoton2.getDirection()<<std::endl;
    }

    if (filter.getOutDir(testPhoton2)){
        if(rec1.getOutDir(testPhoton2,trace)) {
            std::cout << "New direction 3: " << testPhoton2.getDirection() << std::endl;
        }
    }

    if (filter.getOutDir(testPhoton3)){
        if(rec1.getOutDir(testPhoton3,trace)) {
            std::cout << "New direction 4: " << testPhoton2.getDirection() << std::endl;
        }
        std::cout << "this"<< std::endl;
    }else{
        std::cout << "that"<< std::endl;
    }


};