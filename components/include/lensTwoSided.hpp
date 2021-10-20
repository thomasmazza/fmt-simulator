#pragma once

#include "component.hpp"
#include "../../photon/include/photon.hpp"

class LensTwoSided: public Component {
private:
    double n;
    double radiusH;
    double radiusI;
    double radiusO;
    double d;
public:
    LensTwoSided(std::vector<double>&, std::vector<double>&, double, double, double, double, double);
    LensTwoSided(const LensTwoSided& lensTwoSided1);
    bool getOutDir(Photon&);
    const double& getN();
    const double& getRadiusH();
    const double& getRadiusI();
    const double& getRadiusO();
    const double& getD();
    void setN(double _n);
    void setRadiusH(double _radiusH);
    void setRadiusI(double  _radiusI);
    void setRadiusO(double _radiusO);
    void setD(double _d);
};
