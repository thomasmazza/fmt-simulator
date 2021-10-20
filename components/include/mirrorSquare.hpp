#pragma once

#include "component.hpp"
#include "../../photon/include/photon.hpp"

class MirrorSquare : public Component {
private:
    double length;
public:
    MirrorSquare(std::vector<double> &, std::vector<double> &, double);

    MirrorSquare(const MirrorSquare& mirrorSquare1);

    bool calcOut(Photon &, std::vector<double> &, std::vector<double> &);

    bool getOutDir(Photon &, std::vector<double> &);

    void setLength(double  _length);

    std::string getType();
    const double &getLength();
};
