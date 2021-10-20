#pragma once

#include "mirrorElliptical.hpp"

class MirrorCircle : public MirrorElliptical{
    private:
    public:
    MirrorCircle(std::vector<double>&, std::vector<double>&, double);
    MirrorCircle(const MirrorCircle& mirrorCircle1);
    const double getRadius();
};
