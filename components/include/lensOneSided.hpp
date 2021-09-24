#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "lens.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

class LensOneSided: public Lens {
private:
    double radiusW;
    bool planeIsFront;
public:
    LensOneSided(vector&, vector&, double, double, double, bool);
    double getRadiusW();
    bool getPlaneIsFront();
    std::string getType();
};
