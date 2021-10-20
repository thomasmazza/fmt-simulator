#pragma once

#include "mirror.hpp"

class MirrorElliptical: public Mirror{
    private:
        double radiusH;
        double radiusW;
    protected:
    MirrorElliptical(std::vector<double>&, std::vector<double>&, double, double, ComponentType _type);
    public:
        MirrorElliptical(std::vector<double>&, std::vector<double>&, double, double);
        MirrorElliptical(const MirrorElliptical& mirrorElliptical1);
        bool calcOut(Photon&, std::vector<double>&, std::vector<double>&);
        bool getOutDir(Photon&, std::vector<double>&);
        const double& getRadiusH();
        const double& getRadiusW();
        void setRadiusH(double  _radiusH);
        void setRadiusW(double _radiusW);
};
