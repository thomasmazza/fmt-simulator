#include<iostream>
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
#include "exporter.hpp"


typedef typename std::vector<RGB> rgb_vector;
typedef typename std::vector<BmpRGB> bmp_vector;

int main() {
    std::cout << " BBB " << std::endl;
    int S = 512;
    std::vector v(3);
    for (int i = 0; i < 3; i++) {
        v[i] = 0;
    }
    Photon ph(v, v, 420, 0);
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
            ph.setWaveLength(wl);
            phV.push_back(ph);
            if (i > j) {
                phV.push_back(ph);
                phV.push_back(ph);
                phV.push_back(ph);
            }
        }
    }
    std::cout << " BBB " << std::endl;

    std::vector pos (3);
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 2;

    std::vector poe(3);
    poe[0] = 0;
    poe[1] = 0.5;
    poe[2] = 2;

    std::vector ppc(3);
    ppc[0] = 0;
    ppc[1] = 0;
    ppc[2] = 0;

    Detector d(pos, pos, poe, ppc, 100, 0.01);
    for (int i = 0; i < phV.size(); i++) {
        d.getInPoint(phV[i]);
    }

    return 0;
}