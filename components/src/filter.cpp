#include "../include/filter.hpp"
#include "../../photon/include/photon.hpp"
int Filter::getLowerLimit() {
    return lowerLimit;
}

void Filter::setLowerLimit(int _lowerLimit) {
    lowerLimit= _lowerLimit;
}

int Filter::getUpperLimit() {
    return upperLimit;
}

void Filter::setUpperLimit(int _upperLimit) {
    upperLimit = _upperLimit;
}

bool Filter::inRange(int lambda) {
    if (lambda > upperLimit || lambda < lowerLimit) return false;
    return true;
}
std::string Filter::getType() {
    return "Filter";
}

Filter::Filter(std::vector<double>& _pos, std::vector<double>& _normal, int _lowerLimit, int _upperLimit):Component(_pos, _normal,  filter),lowerLimit(_lowerLimit),upperLimit(_upperLimit){}

Filter::Filter(const Filter &filter1): Component(filter1), upperLimit(filter1.upperLimit), lowerLimit(filter1.lowerLimit) {}

bool Filter::getOutDir(Photon& p){
    return inRange(p.getWaveLength());
}

