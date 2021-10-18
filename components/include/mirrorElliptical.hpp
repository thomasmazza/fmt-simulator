#pragma once

#include "mirror.hpp"

class MirrorElliptical: public Mirror{
    private:
        double rH;
        double rW;
    public:
        MirrorElliptical(vector&, vector&, double, double);
        bool calcOut(Photon&, vector&, vector&);
        bool getOutDir(Photon&, vector&);
};
