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


void bitmap(int & _width, int & _height, bmp_vector & _im) {
    BmpFileHeader bfh(_width, _height);
    BmpInfoHeader bih(_width, _height);
    unsigned short bfType=0x4d42;

    FILE *file = fopen("output.bmp", "wb");

    fwrite(&bfType,1,sizeof(bfType),file);
    fwrite(&bfh, 1, sizeof(bfh), file);
    fwrite(&bih, 1, sizeof(bih), file);

    for (int y = bih.height-1; y>=0; y--)
    {
        for (int x = 0; x < bih.width; x++)
        {
            unsigned char r = _im[y * bih.height + x].r;
            unsigned char g = _im[y * bih.height + x].g;
            unsigned char b = _im[y * bih.height + x].b;
            fwrite(&b, 1, 1, file);
            fwrite(&g, 1, 1, file);
            fwrite(&r, 1, 1, file);
        }
    }
    fclose(file);
}


int main() {
    std::cout << " BBB " << std::endl;
    int S = 256;
    std::vector<double> v(3);
    for (int i = 0; i < 3; i++) {
        v[i] = 0;
    }
    Photon ph(v, v, 420);
    std::vector<Photon> phV;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            v[0] = j / 100.0;
            v[1] = i / 100.0;
            v[2] = 0.0;
            ph.setPosition(v);
            v[0] = 0.0;
            v[1] = 0.0;
            v[2] = 1.0;
            ph.setDirection(v);
            int wl = 420;
            phV.push_back(ph);
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

    Detector d(pos, pos, poe, ppc, S, 0.0014);
    for (int i = 0; i < phV.size(); i++) {
        d.getInPoint(phV[i]);
    }

    bmp_vector image = d.createImage();
    bitmap(S, S, image);
    return 0;
}