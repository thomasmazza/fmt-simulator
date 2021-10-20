#pragma once

#include "component.hpp"
#include "../../photon/include/photon.hpp"

class MirrorRectangle : public Component {
private:
    double lengthH;
    double lengthW;
public:
    MirrorRectangle(std::vector<double> &, std::vector<double> &, double, double);

    MirrorRectangle(const MirrorRectangle& mirrorRectangle1);

    bool calcOut(Photon &, std::vector<double> &, std::vector<double> &);

    bool getOutDir(Photon &, std::vector<double> &);

    const double &getLengthH();

    const double &getLengthW();

    void setLengthH(double  _lengthH);

    void setLengthW(double _lengthW);
};

