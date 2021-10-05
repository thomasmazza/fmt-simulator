#pragma once

#include "lens.hpp"
#include "utils.hpp"


class LensTwoSided: public Lens {
private:
    double radius1;
    double radius2;
public:
    LensTwoSided(vector&, vector&, double, double, double, double, double);
    bool getOutDir(Photon&);
};
