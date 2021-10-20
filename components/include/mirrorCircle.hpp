#pragma once

#include "mirrorElliptical.hpp"

class MirrorCircle : public MirrorElliptical{
    public:
    MirrorCircle(std::vector<double>&, std::vector<double>&, double);
    const double getRadius();
};
