#pragma once

#include "lens.hpp"
#include "utils.hpp"


class LensOneSided: public Lens {
private:
    double radiusW;
    bool planeIsFront;
public:
    LensOneSided(vector&, vector&, double, double, double, double, bool);
    bool getOutDir(Photon&);
};
