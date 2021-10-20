#pragma once

#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;
class Utils {
public:
    static void cross_product(vector &, vector &, vector &);

    static vector cross_product_2(vector &, vector &);

    static void normalizeVector(vector &);

    static double dot_product(vector &, vector &);

    static std::string wavelengthToRGB(const int &);

    static void coreTranslationInColor(const int &, double &, double &, double &);

    static double max(double, double);

    static double min(double, double);

    static double depthOfField(double &, double &);
};