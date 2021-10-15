#pragma once

#include <iostream>
#include <boost/numeric/ublas/io.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include "../../photon/include/photon.hpp"
#include "component.hpp"
#include "math.h"
#include "utils.hpp"


class Lens: public Component {
protected:
    double radiusH;
    double n;
    double d;
public:
    Lens(std::vector<double>&, std::vector<double>&, double, double, double, ComponentType _type);
    virtual bool getOutDir(Photon&)=0;
    const double& getN();
    const double& getRadiusH();
    const double& getD();
};
