#pragma once

#include "lens.hpp"
#include "../../utils/include/utils.hpp"


class LensTwoSided: public Lens {
private:
    double radiusI;
    double radiusO;
public:
    LensTwoSided(std::vector<double>&, std::vector<double>&, double, double, double, double, double);
    LensTwoSided(const LensTwoSided& lensTwoSided1);
    bool getOutDir(Photon&);
    const double& getRadiusI();
    const double& getRadiusO();
};
