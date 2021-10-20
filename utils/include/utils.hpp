#pragma once

#include <boost/numeric/ublas/vector.hpp>

class Utils {
public:
/*
 * Erster Vektor ist der Ergebnisvektor
 * Zweiter und Dritter Vektor sind die b
 */
    static void cross_product(std::vector<double> &, std::vector<double> &, std::vector<double> &);

    static std::vector<double> cross_product_2(std::vector<double>&, std::vector<double>&);

    static void normalizeVector(std::vector<double> &);

    static double dot_product(std::vector<double>&, std::vector<double>&);

    static std::string wavelengthToRGB(const int&);

    static void coreTranslationInColor(const int&, double&, double&, double&);

    static double max(double, double);

    static double min(double, double);

    static double depthOfField(double &, double &);
};