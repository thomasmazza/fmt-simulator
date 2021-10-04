#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "lens.hpp"
#include "utils.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

class LensTwoSided: public Lens {
private:
    double radius1;
    double radius2;
public:
    LensTwoSided(vector&, vector&, double, double, double, double);
};
