#pragma once

#include "mirror.hpp"

class MirrorRectangle: public Mirror{
    private:
        double lengthH;
        double lengthW;
    public:
        MirrorRectangle(vector&, vector&, double, double);
};
