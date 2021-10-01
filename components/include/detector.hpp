#pragma once

#include <boost/numeric/ublas/vector.hpp>

class Detector {
protected:
    vector position;
    vector normal;
    int size;
    double pixelSize;
public:
    Detector(vector& position, vector& normal, int size, double pixelSize);
};
