#pragma once

#include "lens.hpp"
#include "utils.hpp"


class LensOneSided: public Lens {
private:
    double radiusW;
    bool planeIsFront;
public:
    LensOneSided(std::vector<double>&, std::vector<double>&, double, double, double, double, bool);
    bool getOutDir(Photon&);
    const double& getRadiusW();
    const bool& getPlaneIsFront();
};
