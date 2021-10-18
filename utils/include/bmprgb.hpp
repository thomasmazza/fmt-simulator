#pragma once

#include <cstdint>
#include "rgb.hpp"

struct BmpRGB {
    uint8_t b;
    uint8_t g;
    uint8_t r;

    BmpRGB();

    BmpRGB(RGB &);

    void setBmpRGB(RGB &);
};