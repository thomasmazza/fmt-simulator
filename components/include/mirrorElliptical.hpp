#pragma once

#include "mirror.hpp"
#include "../../utils/include/utils.hpp"

class MirrorElliptical: public Mirror{
    private:
        double radiusH;
        double radiusW;
    public:
        MirrorElliptical(std::vector<double>&, std::vector<double>&, double, double);
        MirrorElliptical(std::vector<double>&, std::vector<double>&, double, double, ComponentType _type);
        bool getOutDir(Photon&, std::vector<double>&, std::vector<double>&);
        bool hitComponent(Photon&, std::vector<double>&);
        const double& getRadiusH();
        const double& getRadiusW();
};
