#include "rgb.hpp"
#include<cmath>

/**
 * @brief Sets the attributes r,g and b
 * @param _r Corresponding red value
 * @param _g Corresponding green value
 * @param _b Corresponding blue value
 */
void RGB::setRGB(double &_r, double &_g, double &_b) {
    r = _r;
    g = _g;
    b = _b;
}

/**
 * @brief Performs additive mixing of colors, but without the averaging division
 * @param _rgb Object from class RGB
 */
void RGB::addRGB(RGB & _rgb) {
    r = r + _rgb.r;
    g = g + _rgb.g;
    b = b + _rgb.b;
}

/**
 * @brief Default constructor, initializes all attributes with 0
 */
RGB::RGB() : r(0), g(0), b(0), intensity(0) {}

/**
 * @brief Constructor, initializes the attributes. Parameters are passed by reference
 * @param _r Corresponding red value
 * @param _g Corresponding green value
 * @param _b Corresponding blue value
 * @param _i Corresponding intensity value
 */
RGB::RGB(double &_r, double &_g, double &_b, double &_i) {
    r = _r;
    g = _g;
    b = _b;
    intensity = _i;
}

/**
 * @brief Constructor, initializes the attributes. Parameters are passed by value
 * @param _r Corresponding red value
 * @param _g Corresponding green value
 * @param _b Corresponding blue value
 * @param _i Corresponding intensity value
 */
RGB::RGB(double _r, double _g, double _b, double _i) {
    r = _r;
    g = _g;
    b = _b;
    intensity = _i;
}

/**
 * @brief Copy constructor
 * @param obj Object from class RGB
 */
RGB::RGB(const RGB &obj) {
    r = obj.r;
    g = obj.g;
    b = obj.b;
    intensity = obj.intensity;
}
