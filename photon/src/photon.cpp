#include "../include/photon.hpp"
#include "../../utils/include/utils.hpp"

std::vector<double> Photon::getPosition() {
    return position;
}

std::vector<double> Photon::getDirection() {
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

void Photon::setPosition(std::vector<double> & _position) {
    position = _position;
}

void Photon::setDirection(std::vector<double> & _direction) {
    Utils::normalizeVector(_direction);
    direction = _direction;
}

Photon::Photon(std::vector<double> & _position, std::vector<double> & _direction, int _waveLength, int _intensity):
waveLength(_waveLength),
position(_position),
direction(_direction),
intensity(_intensity) {
}