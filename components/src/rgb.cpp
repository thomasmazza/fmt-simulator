#include "../include/rgb.hpp"

void RGB::setRGB(double & _r, double & _g, double & _b) {
    r = _r;
    g = _g;
    b = _b;
}

void RGB::addRGB(RGB& _rgb) {
    r = r + _rgb.r;
    g = g + _rgb.g;
    b = b + _rgb.b;
}

RGB::RGB() : r(0), g(0), b(0), intensity(0) {}

RGB::RGB(double & _r, double & _g, double & _b, double & _i) {
    r = _r;
    g = _g;
    b = _b;
    intensity = _i;
}

RGB::RGB(double _r, double _g, double _b, double _i) {
    r = _r;
    g = _g;
    b = _b;
    intensity = _i;
}

RGB::RGB(const RGB & obj)  {
    r = obj.r;
    g = obj.g;
    b = obj.b;
    intensity = obj.intensity;
}
