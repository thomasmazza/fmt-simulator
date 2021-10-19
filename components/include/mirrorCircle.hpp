#pragma once

#include "mirrorElliptical.hpp"

class MirrorCircle : public MirrorElliptical{
    private:
    public:
    MirrorCircle(std::vector<double>&, std::vector<double>&, double);
    std::string getType();
    const double getRadius();
};
