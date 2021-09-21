#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "component.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

class LensTwoSided: public Lens {
private:
    double radiusI;
    double radiusO;
public:
    LensTwoSided(vector&, vector&, double, double, double, double);
};
