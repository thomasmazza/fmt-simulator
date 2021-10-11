#include "../include/utils.hpp"
#include "math.h"

void cross_product(vector& result,vector& a, vector& b){
    result(0)=a(1)*b(2)-a(2)*b(2);
    result(1)=a(2)*b(0)-a(0)*b(2);
    result(2)=a(0)*b(1)-a(1)*b(0);
}

vector cross_product_2(vector& a, vector& b) {
    vector result(3);
    result(0)=a(1)*b(2)-a(2)*b(2);
    result(1)=a(2)*b(0)-a(0)*b(2);
    result(2)=a(0)*b(1)-a(1)*b(0);
    return result;
}

void normalizeVector(vector& a) {
    double t = sqrt(a(0)^2 + a(1)^2 + a(2)^2);
    a(0) = a(0) / t;
    a(1) = a(1) / t;
    a(2) = a(2) / t;
}

double dot_product(vector& a, vector& b) {
    return sqrt(a(0) * b(0) + a(1) * b(1) + a(2) * b(2));
}

std::string Utils::wavelengthToRGB(const int &wavelength) {
    double r = 0;
    double g = 0;
    double b = 0;
    coreTranslationInColor(wavelength, r, g, b);
    std::string result = "#";
    std::stringstream stream;
    stream << std::hex << (int) r;
    if (stream.str().length() < 2) {
        result += "0" + stream.str();
    } else {
        result += stream.str();
    }
    stream.str("");
    stream << std::hex << (int) g;
    if (stream.str().length() < 2) {
        result += "0" + stream.str();
    } else {
        result += stream.str();
    }
    stream.str("");
    stream << std::hex << (int) b;
    if (stream.str().length() < 2) {
        result += "0" + stream.str();
    } else {
        result += stream.str();
    }
    return result;
}

//Hauptumrechnung in Farbe
void Utils::coreTranslationInColor(const int &wavelength, double &r, double &g, double &b) {
    const double dWavelength = static_cast<double>(wavelength);
    if (dWavelength >= 380 && dWavelength <= 440) {
        r = -1 * (dWavelength - 440) / (440 - 380);
        g = 0;
        b = 1;
    } else if (dWavelength > 440 && dWavelength <= 490) {
        r = 0;
        g = (dWavelength - 440) / (490 - 440);
        b = 1;
    } else if (dWavelength > 490 && dWavelength <= 510) {
        r = 0;
        g = 1;
        b = -1 * (dWavelength - 510) / (510 - 490);
    } else if (dWavelength > 510 && dWavelength <= 580) {
        r = (dWavelength - 510) / (580 - 510);
        g = 1;
        b = 0;
    } else if (dWavelength > 580 && dWavelength <= 645) {
        r = 1;
        g = -1 * (dWavelength - 645) / (645 - 580);
        b = 0;
    } else if (dWavelength > 645 && dWavelength <= 780) {
        r = 1;
        g = 0;
        b = 0;
    }

    // Intensitaetsanpassungen an den Raendern
    double intensity = 1;
    if (dWavelength >= 700) {
        intensity = 0.3 + 0.7 * (780 - dWavelength) / (780 - 700);
    } else if (dWavelength < 420) {
        intensity = 0.3 + 0.7 * (dWavelength - 380) / (420 - 380);
    }
    // Rounding to integers
    r = round(r * intensity * 255);
    g = round(g * intensity * 255);
    b = round(b * intensity * 255);

}