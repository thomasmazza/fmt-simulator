#include "../include/filter.hpp"
#include "../../photon/include/photon.hpp"

/**
 * @brief Standard get-method for getting the lower limit of the filter
 * @return lower limit of the filter
 */
int Filter::getLowerLimit() {
    return lowerLimit;
}

/**
 * @brief Standard set-method for setting the lower limit of the filter
 * @param _lowerLimit, sets the new lower limit of the filter
 */
void Filter::setLowerLimit(int _lowerLimit) {
    lowerLimit= _lowerLimit;
}

/**
 * @brief Standard get-method for getting the upper limit of the filter
 * @return upper limit of the filter
 */
int Filter::getUpperLimit() {
    return upperLimit;
}

/**
 * @brief Standard set-method for setting the upper limit of the filter
 * @param _upperLimit, sets the new upper limit of the filter
 */
void Filter::setUpperLimit(int _upperLimit) {
    upperLimit = _upperLimit;
}

/**
 * @brief bool method for checking if the wavelength of the current photon is in range
 * @param lambda, wavelength of a photon
 * @return true, if the wavelength is in range
 */
bool Filter::inRange(int lambda) {
    if (lambda > upperLimit || lambda < lowerLimit) return false;
    return true;
}

/**
 * @brief Standard get-method for getting the current type of the component
 * @return type of the current component ("Filter")
 */
std::string Filter::getType() {
    return "Filter";
}

/**
 * @brief Constructs a filter
 * @param _position, sets the position of the new filter
 * @param _normal, sets the normal of the new filter
 * @param _lowerLimit, sets the lower limit of the new filter
 * @param _upperLimit, sets the upper limit of the new filter
 * @param _type, sets the type of the component ("Filter")
 */
Filter::Filter(std::vector<double>& _pos, std::vector<double>& _normal, int _lowerLimit, int _upperLimit):Component(_pos, _normal,  filter),lowerLimit(_lowerLimit),upperLimit(_upperLimit){}

/**
 * @brief Copys a filter
 * @param filter1, copy template for the new filter
 */
Filter::Filter(const Filter &filter1): Component(filter1), upperLimit(filter1.upperLimit), lowerLimit(filter1.lowerLimit) {}

/**
 * @brief Main function of every component, calculates the position and direction after the photon passes
 * @param photon, Photon who should be calculated
 */
bool Filter::getOutDir(Photon& p){
    return inRange(p.getWaveLength());
}

