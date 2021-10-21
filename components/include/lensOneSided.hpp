#pragma once

#include "component.hpp"
#include "../../photon/include/photon.hpp"

class LensOneSided: public Component {
private:
    double n;
    double radiusH;
    double radiusW;
    double d;
    double f;
    bool planeIsFront;
public:
    LensOneSided(std::vector<double>&, std::vector<double>&, double, double, double, double, bool);
    LensOneSided(const LensOneSided& lensOneSided1);
    bool getOutDir(Photon&);
    const double& getN();
    const double& getRadiusH();
    const double& getD();
    const double& getF();
    const double& getRadiusW();
    const bool& getPlaneIsFront();
    void setN(double _n);
    void setRadiusH(double _radiusH);
    void setD(double _d);
    void setRadiusW(double _radiusW);
    void setPlaneIsFront(bool _planeIsFront);
};
