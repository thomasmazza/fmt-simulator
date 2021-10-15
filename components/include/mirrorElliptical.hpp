#pragma once

#include "mirror.hpp"

class MirrorElliptical: public Mirror{
    private:
        double radiusH;
        double radiusW;
    public:
        MirrorElliptical(std::vector<double>&, std::vector<double>&, double, double);
        MirrorElliptical(std::vector<double>&, std::vector<double>&, double, double, ComponentType _type);
        bool calcOut(Photon&, std::vector<double>&, std::vector<double>&);
        bool getOutDir(Photon&, std::vector<double>&);
        const double& getRadiusH();
        const double& getRadiusW();
};
