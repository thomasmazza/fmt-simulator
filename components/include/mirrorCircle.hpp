#pragma once

#include "../include/mirrorElliptical.hpp"

class MirrorCircle : public MirrorElliptical{
    private:
    public:
        MirrorElliptical(vector&, vector&, double);
        std::string getType();
};
