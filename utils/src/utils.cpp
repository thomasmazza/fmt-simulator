#include "../include/utils.hpp"
#include <cmath>
#include <iomanip>

/**
 * @brief Calculates the cross product of 2 vectors
 * @param result The resulting vector
 * @param a First vector
 * @param b Second vector
 */
void Utils::cross_product(std::vector<double> &result, std::vector<double> &a, std::vector<double> &b) {
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

/**
 * @brief Calculates the cross product of 2 vectors, but returns the result
 * @param a First vector
 * @param b Second vector
 * @return The resulting vector
 */
std::vector<double> Utils::cross_product_2(std::vector<double>& a, std::vector<double>& b) {
    std::vector<double> result(3);
    result[0]=a[1]*b[2]-a[2]*b[2];
    result[1]=a[2]*b[0]-a[0]*b[2];
    result[2]=a[0]*b[1]-a[1]*b[0];
    return result;
}

/**
 * @brief Calculates RGB as hex strings
 * @param wavelength
 * @return RGB value as hex
 */
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
/**
 * @brief Calculates the RGB value for a given wavelength
 * @param wavelength Wavelength
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 */
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

/**
 * @brief Scales the vector to a length of 1
 * @param _vec Vector to scale
 */
void Utils::normalizeVector(std::vector<double> &_vec) {
    double vecAbs = 0;
    //Laenge des Vektors bestimmen
    for (int i = 0; i < 3; i++) vecAbs += pow(_vec[i], 2);
    vecAbs = sqrt(vecAbs);

    //Normierten Vektor berechnen
    for (int i = 0; i < 3; i++) _vec[i] = (_vec[i] / vecAbs);
}

/**
 * @brief Returns the maximum of two double values
 * @param a First value
 * @param b Second value
 * @return The bigger of a and b. If they are equal, a is returned
 */
double Utils::max(double a, double b) {
    if (a < b) { return b; }
    else return a;
}

/**
 * @brief Returns the minimum of two double values
 * @param a First value
 * @param b Second value
 * @return The smaller of a and b. If they are equal, a is returned
 */
double Utils::min(double a, double b) {
    if (a > b) { return b; }
    else return a;
}

/**
 * @brief Calculates the dot product of two vectors
 * @param a First vector
 * @param b Second vector
 * @return The dot product of a and b
 */
double Utils::dot_product(std::vector<double>& a, std::vector<double>& b) {
    return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

// Approximiert die Tiefenschärfe bei konstanter Blende
// _f = Brennweite der Linse
// _d = Abstand zum Objekt
// _f / 1720 approximiert das CoC (Circle of Confusion); Wir können auch anderes Modell für CoC nehmen, zB Detektordiagonal/1442;
// Wir können auch uns einfach überlegen was wir als akzeptables CoC nehmen;
// Ich bin nicht sicher wie wir depthOfField sinnvoll auf [0,100] normieren können, denn depthOfField kann technisch von 0 bis unendlich groß sein;
/**
 * @brief Approximates the depth of field given distance to object and focal length
 * @param _f
 * @param _d
 * @return Depth of field
 */
double Utils::depthOfField(double & _f, double & _d) {
    return 2 * (_f / 1720) * pow((_d / _f), 2);
}

/** the Euclidean norm vector
 * @param _vec Vector
 * @return The Euclidean norm of vector
 */
double Utils::getAbs(std::vector<double> &_vec) {
    double vecAbs = 0;
    //Laenge des Vektors bestimmen
    for (int i = 0; i < 3; i++) vecAbs += pow(_vec[i], 2);
    vecAbs = sqrt(vecAbs);
    return vecAbs;
}
