#pragma once

#include "mirror.hpp"
class RectangleMirror: public Mirror{
    private:
        double lengthH;
        double lengthW;
    public:
        RectangleMirror(vector&, vector&, double, double);
};
