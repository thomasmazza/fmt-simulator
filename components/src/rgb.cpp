#include "../include/rgb.hpp"

void RGB::setRGB(double & _r, double & _g, double & _b) {
    r = _r;
    g = _g;
    b = _b;
}

RGB::RGB() : r(0), g(0), b(0) {}

RGB::RGB(double & _r, double & _g, double & _b) {
    r = _r;
    g = _g;
    b = _b;
}
