#pragma once

#include "../../utils/include/utils.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include "../../photon/include/photon.hpp"
#include "component.hpp"
#include "math.h"

typedef typename boost::numeric::ublas::vector<double> vector;

class Lens : public Component {
protected:
    double n;
    double radiusH;
    double d;
public:
    Lens(vector &, vector &, double, double, double);

    virtual bool getOutDir(Photon &) = 0;
};
