#pragma once

#include "mirror.hpp"

class MirrorElliptical: public Mirror{
    private:
        double rH;
        double rW;
    public:
        MirrorElliptical(vector&, vector&, double, double);
        bool getOutDir(Photon&, vector&, vector&)=0;
        bool hitComponent(Photon&, vector&)=0;
};
