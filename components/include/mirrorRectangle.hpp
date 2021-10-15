#pragma once

#include "mirror.hpp"

class MirrorRectangle: public Mirror{
    private:
        double lengthH;
        double lengthW;
    public:
        MirrorRectangle(std::vector<double>&, std::vector<double>&, double, double);
        MirrorRectangle(std::vector<double>&, std::vector<double>&, double, double, ComponentType _type);
        bool calcOut(Photon&, std::vector<double>&, std::vector<double>&);
        bool getOutDir(Photon&, std::vector<double>&);
        const double& getLengthH();
        const double& getLengthW();
};

