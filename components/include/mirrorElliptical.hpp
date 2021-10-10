#pragma once

#include "mirror.hpp"
#include "../../utils/include/utils.hpp"

class MirrorElliptical: public Mirror{
    private:
        double rH;
        double rW;
    public:
        MirrorElliptical(vector&, vector&, double, double);
        bool getOutDir(Photon&, vector&, vector&);
        bool hitComponent(Photon&, vector&);
};
