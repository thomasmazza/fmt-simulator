#pragma once

#include "mirror.hpp"

class MirrorRectangle : public Mirror {
private:
    double lengthH;
    double lengthW;
protected:
    MirrorRectangle(std::vector<double> &, std::vector<double> &, double, double, ComponentType _type);

public:
    MirrorRectangle(std::vector<double> &, std::vector<double> &, double, double);

    MirrorRectangle(const MirrorRectangle& mirrorRectangle1);

    bool calcOut(Photon &, std::vector<double> &, std::vector<double> &);

    bool getOutDir(Photon &, std::vector<double> &);

    const double &getLengthH();

    const double &getLengthW();
};

