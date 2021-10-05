#pragma once

#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include "../../photon/include/photon.hpp"
#include "component.hpp"
#include "math.h"
#include "utils.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

class Lens: public Component {
protected:
    double n;
    double radiusH;
    double d;
public:
    Lens(vector&, vector&, double, double, double);
    virtual bool getOutDir(Photon&)=0;
};
