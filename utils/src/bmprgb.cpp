#include "bmprgb.hpp"
#include <cstdint>
#include <cmath>

BmpRGB::BmpRGB(): b(0), g(0), r(0) {}

BmpRGB::BmpRGB(RGB& color) {
    uint32_t t = round(color.b);
    b = t & 0xFF;
    t = round(color.g);
    g = t & 0xFF;
    t = round(color.r);
    r = t & 0xFF;
}

void BmpRGB::setBmpRGB(RGB& color) {
    uint32_t t = round(color.b);
    b = t & 0xFF;
    t = round(color.g);
    g = t & 0xFF;
    t = round(color.r);
    r = t & 0xFF;
}

