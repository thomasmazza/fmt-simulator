#pragma once

#include "mirror.hpp"

class EllipticalMirror: public Mirror{
    private:
        double rH;
        double rW;
    public:
        EllipticalMirror(vector&, vector&, double, double);
};
