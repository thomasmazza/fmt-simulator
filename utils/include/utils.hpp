#pragma once

#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;
class Utils {
private:
    static void coreTranslationInColor(const int&, double&, double&, double&);
public:
/*
 * Erster Vektor ist der Ergebnisvektor
 * Zweiter und Dritter Vektor sind die b
 */
    static void cross_product(vector &, vector &, vector &);

    static std::string wavelengthToRGB(const int&);

    static void normalizeVector(vector& _vec);
};