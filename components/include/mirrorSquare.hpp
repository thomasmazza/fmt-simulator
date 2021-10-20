#pragma once

#include "mirrorRectangle.hpp"

class MirrorSquare: public MirrorRectangle{
    public:
        MirrorSquare(std::vector<double>&, std::vector<double>&, double);
    const double& getLength();
};
