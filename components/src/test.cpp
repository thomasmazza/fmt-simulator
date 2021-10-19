
#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <vector>
#include <fstream>
#include "../../utils/include/utils.hpp"
#include "detector.hpp"
#include "rgb.hpp"
#include "lensOneSided.hpp"
#include "lens.hpp"
#include "filter.hpp"
#include "lensTwoSided.hpp"
#include "mirrorElliptical.hpp"
#include "mirrorRectangle.hpp"
#include "bmprgb.hpp"
#include "bmpFileHeader.hpp"
#include "bmpInfoHeader.hpp"


typedef typename std::vector<RGB> rgb_vector;
typedef typename std::vector<BmpRGB> bmp_vector;

int main(int argc, char *argv[]) {
    std::vector<double> testVector(3);
    std::vector<double> testVector2(3);
    std::vector<double> testVector3(3);
    std::vector<double> testVector4(3);
    std::vector<double> testVector5(3);

    std::vector<double> filterPos(3);
    std::vector<double> filterDir(3);

    testVector2[0] = -1;
    testVector2[1] = 0;
    testVector2[2] = 0;

    testVector3[0] = -1;
    testVector3[1] = 1;
    testVector3[2] = 1;

    testVector4[0] = 1;
    testVector4[1] = 0;
    testVector4[2] = 0;

    testVector5[0] = -1;
    testVector5[1] = 0;
    testVector5[2] = 1;

    filterPos[0] = 0;
    filterPos[1] = 1;
    filterPos[2] = 1;

    filterDir[0] = -1;
    filterDir[1] = 0;
    filterDir[2] = 0;


    int sum1 = 0;
    for (int i = 0; i < 3; i++) {
        sum1 += pow(testVector4[i], 2);
    }
    sum1 = sqrt(sum1);
    for (int i = 0; i < 3; i++) {
        testVector4[i] = testVector4[i] / sum1;
    }

    for (unsigned i = 0; i < testVector.size(); i++) {
        testVector[i] = 1;
    }


    LensTwoSided lens2(testVector, testVector2, 1.5, 10, -30, 30, 5);
    Photon testPhoton(testVector3, testVector4, 600);
    Filter filter(filterPos, filterDir, 450, 700);


    testVector[0] = 10;

    LensOneSided lens1(testVector, testVector2, 1.5, 20, 21, 5, false);

    //test mirror

    testVector[0] = 1;
    double Z = 0;
    for (int i = 0; i < 3; i++) {
        Z += pow(testVector5[i], 2);
    }
    Z = sqrt(Z);
    for (int i = 0; i < 3; i++) {
        testVector5[i] = testVector5[i] / Z;
    }

    MirrorRectangle rec1(testVector, testVector5, 20, 20);
    Photon testPhoton2(testVector3, testVector4, 600);
    Photon testPhoton3(testVector3, testVector4, 800);
    std::vector<double> trace(3);
    trace = rec1.getPosition() - testPhoton2.getPosition();

    Z = 0;
    for (int i = 0; i < 3; i++) {
        Z += pow(trace[i], 2);
    }
    Z = sqrt(Z);
    for (int i = 0; i < 3; i++) {
        trace[i] = trace[i] / Z;
    }

    if (rec1.getOutDir(testPhoton2, trace)) {
        std::cout << "New direction 3: " << testPhoton2.getDirection() << std::endl;
    }

    if (filter.getOutDir(testPhoton2)) {
        if (rec1.getOutDir(testPhoton2, trace)) {
            std::cout << "New direction 3: " << testPhoton2.getDirection() << std::endl;
        }
    }

    if (filter.getOutDir(testPhoton3)) {
        if (rec1.getOutDir(testPhoton3, trace)) {
            std::cout << "New direction 4: " << testPhoton2.getDirection() << std::endl;
        }
        std::cout << "this" << std::endl;
    } else {
        std::cout << "that" << std::endl;
    }

    // Exportiert .bmp
//    bmp_vector image = d.createImage();

//    BmpFileHeader bfh(S,S);
//    BmpInfoHeader bih(S,S);
//    std::ofstream fout("output.bmp", std::ios::binary);
//    fout.write((char *) &bfh, 14);
//    fout.write((char *) &bih, 40);
//    for (int i = 0; i < image.size(); i++) {
//        fout.write((char *) &image[i], 3);
//    }
//    fout.close();



};
