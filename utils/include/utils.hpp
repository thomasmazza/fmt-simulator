#pragma once

#include <boost/numeric/ublas/vector.hpp>

class Utils {
private:
    static void coreTranslationInColor(const int&, double&, double&, double&);
public:
/*
 * Erster Vektor ist der Ergebnisvektor
 * Zweiter und Dritter Vektor sind die b
 */
    static void cross_product(std::vector<double> &, std::vector<double> &, std::vector<double> &);

    static std::string wavelengthToRGB(const int&);

    static void normalizeVector(std::vector<double>& _vec);
};