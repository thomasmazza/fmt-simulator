#pragma once

#include "mirrorRectangle.hpp"

class MirrorSquare : public MirrorRectangle {
public:
    MirrorSquare(std::vector<double> &, std::vector<double> &, double);

    MirrorSquare(const MirrorSquare& mirrorSquare1);

        std::string getType();
        const double &getLength();
};
