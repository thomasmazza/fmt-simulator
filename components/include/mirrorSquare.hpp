#pragma once

#include "mirrorRectangle.hpp"

class MirrorSquare : public MirrorRectangle {
private:
public:
    MirrorSquare(std::vector<double> &, std::vector<double> &, double);

    MirrorSquare(const MirrorSquare& mirrorSquare1);

    const double &getLength();
};
