#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include "../../photon/include/photon.hpp"
#include "component.hpp"
#include "math.h"

typedef typename boost::numeric::ublas::vector<double> vector;

class Lens: public Component {
protected:
    double n2;
    double radiusH;
    double d;
public:
    Lens(vector&, vector&, double, double);
    bool hitComponent(Photon&);
    virtual vector getOutDir(Photon&)=0;
};
