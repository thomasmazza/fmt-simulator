#include<iostream>
#include <vector>
#include <fstream>
#include "../../utils/include/utils.hpp"
#include "detector.hpp"
#include "rgb.hpp"
#include "bmprgb.hpp"
#include "bmpFileHeader.hpp"
#include "bmpInfoHeader.hpp"
#include "photon.hpp"


typedef typename std::vector<RGB> rgb_vector;
typedef typename std::vector<BmpRGB> bmp_vector;

int main() {
    std::cout << " BBB " << std::endl;
    int S = 256;
    std::vector<double> v(3);
    for (int i = 0; i < 3; i++) {
        v[i] = 0;
    }
    Photon ph(v, v, 420);
    std::vector<Photon> phV;
    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 400; j++) {
            v[0] = j / 400.0;
            v[1] = i / 400.0;
            v[2] = 0.0;
            ph.setPosition(v);
            v[0] = 0.0;
            v[1] = 0.0;
            v[2] = 1.0;
            ph.setDirection(v);
            int wl = 420;
            phV.push_back(ph);
            if (i > j) {
                phV.push_back(ph);
                phV.push_back(ph);
                phV.push_back(ph);
            }
        }
    }
    std::cout << " BBB " << std::endl;

    std::vector<double> pos (3);
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 2;

    std::vector<double> poe(3);
    poe[0] = 0;
    poe[1] = 0.5;
    poe[2] = 2;

    std::vector<double> ppc(3);
    ppc[0] = 0;
    ppc[1] = 0;
    ppc[2] = 0;

    Detector d(pos, pos, poe, ppc, 256, 0.007);
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