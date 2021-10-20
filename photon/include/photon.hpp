#pragma once

#include <vector>
class Photon {
private:
    const int waveLength;
    std::vector<double> position;
    std::vector<double> direction;
public:
    Photon(std::vector<double>&, std::vector<double>&, int);
    int getWaveLength();
    std::vector<double> getPosition();
    std::vector<double> getDirection();
    void setPosition(std::vector<double>&);
    void setDirection(std::vector<double>&);
    void setIntensity(int);
};