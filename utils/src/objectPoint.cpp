#include "../include/objectPoint.hpp"

const vector &objectPoint::getPosition() {
    return postion;
}

const int &objectPoint::getWavelength() {
    return wavelength;
}

objectPoint::objectPoint(vector & _position, int & _wavelength):postion(_position), wavelength(_wavelength) {}

