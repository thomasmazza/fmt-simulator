#pragma once

#include "mirrorRectangle.hpp"

class MirrorSquare: public MirrorRectangle{
    private:
    public:
        MirrorSquare(std::vector<double>&, std::vector<double>&, double);
        std::string getType();
        const double& getLength();
};
