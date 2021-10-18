#include"filter.hpp"

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

bool Filter::getOutDir(Photon& p){
    return inRange(p.getWaveLength());
}

Filter::Filter(vector& _pos, vector& _normal, int _lowerLimit, int _upperLimit):Component(_pos, _normal){
    lowerLimit = _lowerLimit;
    upperLimit = _upperLimit;
}
