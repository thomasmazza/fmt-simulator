#include<iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <fstream>
#include "../../utils/include/utils.hpp"
#include "../include/detector.hpp"
#include "rgb.hpp"
#include "bmprgb.hpp"
#include "bmpFileHeader.hpp"
#include "bmpInfoHeader.hpp"
#include "../../photon/include/photon.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename boost::numeric::ublas::vector<RGB> rgb_vector;
typedef typename boost::numeric::ublas::vector<BmpRGB> bmp_vector;

int main() {
    unsigned int S = 256;
    vector v (3);
    for (int i = 0; i < 3; i++) {
        v(i) = 0;
    }

    std::vector<Photon> phV;
    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 400; j++) {
            Photon ph(v, v, 420 + i%3, 0);
            v(0) = j / 400.0;
            v(1) = i / 400.0;
            v(2) = 0.0;
            ph.setPosition(v);
            v(0) = 0.0;
            v(1) = 0.0;
            v(2) = 1.0;
            ph.setDirection(v);
            int wl = 420;
            phV.push_back(ph);
            if (i > j) {
                phV.push_back(ph);
            }
        }
    }

    v(0) = 0.5;
    v(1) = 0.5;
    v(2) = 5.0;

    vector vn(3);
    vn(0) = 0.0;
    vn(1) = 0.0;
    vn(2) = 5.0;

    vector vpe(3);
    vpe(0) = 0.5;
    vpe(1) = 1;
    vpe(2) = 5.0;

    vector vpc(3);
    vpc(0) = 0.5;
    vpc(1) = 0.5;
    vpc(2) = 0.0;

    Detector d(v, vn, vpe, vpc, S, 0.004);

    for (int i = 0; i < phV.size(); i++) {
        d.getInPoint(phV[i]);
    }


    bmp_vector image = d.createImage();

    BmpFileHeader bfh(S,S);
    BmpInfoHeader bih(S,S);
    std::ofstream fout("output.bmp", std::ios::binary);
    fout.write((char *) &bfh, 14);
    fout.write((char *) &bih, 40);
    for (int i = 0; i < image.size(); i++) {
        fout.write((char *) &image[i], 3);
    }
    fout.close();
    return 0;

}