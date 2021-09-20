#pragma once

#include "ellipticalMirror.hpp"
class CircleMirror : public EllipticalMirror{
private:
    double radius;
public:
    CircleMirror(vector&, vector&, vector&, vector&, vector&, double);
};


