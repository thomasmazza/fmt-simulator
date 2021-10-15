#pragma once

#include "lens.hpp"
#include "utils.hpp"


class LensTwoSided: public Lens {
private:
    double radiusI;
    double radiusO;
public:
    LensTwoSided(std::vector<double>&, std::vector<double>&, double, double, double, double, double);
    bool getOutDir(Photon&);
    const double& getRadiusI();
    const double& getRadiusO();
};
