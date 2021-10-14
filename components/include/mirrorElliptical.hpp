#pragma once

#include "mirror.hpp"
#include "../../utils/include/utils.hpp"

class MirrorElliptical: public Mirror{
    private:
        double radiusH;
        double radiusW;
    public:
        MirrorElliptical(vector&, vector&, double, double);
        MirrorElliptical(vector&, vector&, double, double, ComponentType _type);
        bool getOutDir(Photon&, vector&, vector&);
        bool hitComponent(Photon&, vector&);
};
