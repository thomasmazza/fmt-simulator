#include "../include/photon.hpp"
#include "../../utils/include/utils.hpp"
/**
 * @return Position vector of Photon
 */
std::vector<double> Photon::getPosition() {
    return position;
}
/**
 * @return direction vector of Photon
 */
std::vector<double> Photon::getDirection() {
    return direction;
}
/**
 * @return wavelength of vector
 */
int Photon::getWaveLength() {
    return waveLength;
}
/**
 * @brief Setter for Position Vector
 * @param _position new Position Vector
 */
void Photon::setPosition(std::vector<double> &_position) {
    position = _position;
}
/**
 * @brief Setter for Direction Vector and normalize new vector
 * @param _direction new direction vector
 */
void Photon::setDirection(std::vector<double> &_direction) {
    Utils::normalizeVector(_direction);
    direction = _direction;
}
/**
 * @brief Constructor for new Photon
 * @param _position position vector
 * @param _direction direction vector
 * @param _waveLength wavelength
 */
Photon::Photon(std::vector<double> &_position, std::vector<double> &_direction, int _waveLength) :
        waveLength(_waveLength),
        position(_position),
        direction(_direction) {
}