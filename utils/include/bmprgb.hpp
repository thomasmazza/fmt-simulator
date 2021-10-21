#pragma once
#include <vector>
#include <cstdint>
#include "rgb.hpp"

//typedef typename std::vector<BmpRGB> bmp_vector;

struct BmpRGB {
    uint8_t b;
    uint8_t g;
    uint8_t r;

    BmpRGB();

    BmpRGB(RGB &);

    void setBmpRGB(RGB &);
};