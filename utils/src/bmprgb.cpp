#include "bmprgb.hpp"
#include <cstdint>
#include <cmath>

/**
 * @brief Default constructor, initializes the attributes with 0
 */
BmpRGB::BmpRGB(): b(0), g(0), r(0) {}

/**
 * @brief Constructor that converts Objects of type RGB into BmpRGB, ready for .bmp export
 * @param color Object of type RGB
 */
BmpRGB::BmpRGB(RGB& color) {
    uint32_t t = round(color.b);
    b = t & 0xFF;
    t = round(color.g);
    g = t & 0xFF;
    t = round(color.r);
    r = t & 0xFF;
}

/**
 * @brief Sets the red, green and blue values
 * @param color Object of type RGB
 */
void BmpRGB::setBmpRGB(RGB& color) {
    uint32_t t = round(color.b);
    b = t & 0xFF;
    t = round(color.g);
    g = t & 0xFF;
    t = round(color.r);
    r = t & 0xFF;
}

