#include "../include/objectPoint.hpp"

const std::vector<double> &objectPoint::getPosition() {
    return postion;
}

const int &objectPoint::getWavelength() {
    return wavelength;
}

objectPoint::objectPoint(std::vector<double> & _position, int & _wavelength):postion(_position), wavelength(_wavelength) {}

