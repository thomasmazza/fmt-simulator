#include "rgb.hpp"
#include<cmath>
void RGB::setRGB(double &_r, double &_g, double &_b) {
    r = _r;
    g = _g;
    b = _b;
}

void RGB::addRGB(RGB & _rgb) {
    r = r + _rgb.r;
    g = g + _rgb.g;
    b = b + _rgb.b;
}

/*void RGB::calcHS(double & _i, double & _m) {
    double max = r;
    double min = g;
    if (r < g) {
        max = g;
        min = b;
    }
    if (max < b) {
        max = b;
    }
    if (min > b) {
        min = b;
    }
    double c = max - min;
    double r1 = r / 255;
    double g1 = g / 255;
    double b1 = b / 255;
    if (c == 0) {
        h = 0;
    }
    else {
        if (max == r) {
            h = std::fmod(((g1 - b1) / c), 6.0);
        }
        else if (max == g) {
            h = (b1 - r1) / c + 2.0;
        }
        else if (max == b) {
            h = (r1 - g1) / c + 4.0;
        }
        h = h * 60;
        //intensity = (_i / _m) * 0.618;
        s = 1 - (min / ((intensity / _m) * 0.618));
    }


}
 */

RGB::RGB() : r(0), g(0), b(0), intensity(0) {}

RGB::RGB(double &_r, double &_g, double &_b, double &_i) {
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

RGB::RGB(const RGB &obj) {
    r = obj.r;
    g = obj.g;
    b = obj.b;
    intensity = obj.intensity;
}
