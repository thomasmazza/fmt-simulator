#pragma once

#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;
class Photon {
private:
    int waveLength;
    vector position;
    vector direction;
public:
    Photon(vector&, vector&, int);

    int getWaveLength();
    vector getPosition();
    vector getDirection();

    void setWaveLength(int&);
    void setPosition(vector&);
    void setDirection(vector&);
};