#pragma once

#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;
class Photon {
private:
    const int waveLength;
    int intensity;
    vector position;
    vector direction;
public:
    Photon(vector&, vector&, int, int);
    int getWaveLength();
    int getIntensity();
    vector getPosition();
    vector getDirection();
    void setPosition(vector&);
    void setDirection(vector&);
    void setIntensity(int);
};