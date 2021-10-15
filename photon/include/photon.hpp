#pragma once

#include <boost/numeric/ublas/vector.hpp>

class Photon {
private:
    const int waveLength;
    int intensity;
    std::vector<double> position;
    std::vector<double> direction;
public:
    Photon(std::vector<double>&, std::vector<double>&, int, int);
    int getWaveLength();
    int getIntensity();
    std::vector<double> getPosition();
    std::vector<double> getDirection();
    void setPosition(std::vector<double>&);
    void setDirection(std::vector<double>&);
    void setIntensity(int);
};