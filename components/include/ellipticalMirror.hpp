#pragma once
#include "mirror.hpp"
class EllipticalMirror: public Mirror{
    private:
        double rH;
        double rB;
    public:
    EllipticalMirror(vector&, vector&, vector&, vector&, vector&, double, double);
};


