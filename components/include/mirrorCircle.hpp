#pragma once

#include "mirrorElliptical.hpp"

class MirrorCircle : public MirrorElliptical{
    private:
    public:
        MirrorCircle(std::vector<double>&, std::vector<double>&, double);
    const double& getRadius();
};
