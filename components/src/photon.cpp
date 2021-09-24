#include "photon.hpp"

vector Photon::getPosition() {
    return position;
}

vector Photon::getDirection() {
    return direction;
}

int Photon::getWaveLength() {
    return waveLength;
}

void Photon::setWaveLength(int& _waveLength) {
    waveLength =_waveLength;
}

void Photon::setPosition(vector & _position) {
    position = _position;
}

void Photon::setDirection(vector & _direction) {
    direction = _direction;
}

Photon::Photon(vector & _position, vector & _direction, int _waveLength, int _intensity) {
    setWaveLength(_waveLength);
    setPosition(_position);
    setDirection(_direction);
    intensity = _intensity;
}