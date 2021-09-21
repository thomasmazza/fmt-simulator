#pragma once

#include "rectangleMirror.hpp"
class SquareMirror: public RectangleMirror{
    private:
        double length;
    public:
        SquareMirror(vector&, vector&, double);
};
