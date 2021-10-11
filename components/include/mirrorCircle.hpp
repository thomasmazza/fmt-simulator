#pragma once

#include "mirrorElliptical.hpp"
typedef typename boost::numeric::ublas::vector<double> vector;

class MirrorCircle : public MirrorElliptical{
    private:
    public:
        MirrorCircle(vector&, vector&, double);
};
