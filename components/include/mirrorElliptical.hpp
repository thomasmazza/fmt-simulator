#pragma once

#include "mirror.hpp"

class MirrorElliptical: public Mirror{
    private:
        double rH;
        double rW;
    public:
        MirrorElliptical(vector&, vector&, double, double);
};
