#include "../include/photon.hpp"
#include "../../utils/include/utils.hpp"

vector Photon::getPosition() {
    return position;
}

vector Photon::getDirection() {
    return direction;
}

int Photon::getWaveLength() {
    return waveLength;
}

int Photon::getIntensity() {
    return intensity;
}

void Photon::setIntensity(int _intensity) {
    intensity = _intensity;
}

void Photon::setPosition(vector & _position) {
    position = _position;
}

void Photon::setDirection(vector & _direction) {
    Utils::normalizeVector(_direction);
    direction = _direction;
}

Photon::Photon(vector & _position, vector & _direction, int _waveLength, int _intensity):
waveLength(_waveLength),
position(_position),
direction(_direction),
intensity(_intensity) {
}