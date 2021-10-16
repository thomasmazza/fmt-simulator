#include "bmprgb.hpp"
#include <cstdint>

BmpRGB::BmpRGB(): b(0), g(0), r(0) {}

BmpRGB::BmpRGB(RGB& color) {
    uint32_t t = color.b;
    b = t & 0xFF;
    t = color.g;
    g = t & 0xFF;
    t = color.r;
    r = t & 0xFF;
}

void BmpRGB::setBmpRGB(RGB& color) {
    uint32_t t = color.b;
    b = t & 0xFF;
    t = color.g;
    g = t & 0xFF;
    t = color.r;
    r = t & 0xFF;
}

