#pragma once

#include "mirrorElliptical.hpp"

class MirrorCircle : public MirrorElliptical{
    public:
    MirrorCircle(std::vector<double>&, std::vector<double>&, double);
    std::string getType();
    MirrorCircle(const MirrorCircle& mirrorCircle1);
    const double getRadius();
};
