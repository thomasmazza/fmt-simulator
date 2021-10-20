#pragma once

#include "../../utils/include/utils.hpp"
#include "../../photon/include/photon.hpp"
#include "component.hpp"
#include "math.h"


class Lens : public Component {
protected:
    double n;
    double radiusH;
    double d;
public:
    Lens(std::vector<double>&, std::vector<double>&, double, double, double, ComponentType _type);
    virtual bool getOutDir(Photon&)=0;
    const double& getN();
    const double& getRadiusH();
    const double& getD();
    void setN(double _n);
    void setRadiusH(double _radiusH);
    void setD(double _d);
};
