#include "../include/component.hpp"
#include <assert.h>

/**
 * @brief Constructs a component
 * @param _position, sets the position of the new component
 * @param _normal, sets the normal of the new component
 * @param _type, sets the type of the component (e.g. lensTwoSided)
 */
Component::Component(std::vector<double> &_position, std::vector<double> &_normal, ComponentType _type) : position(_position), normal(_normal),
                                                                                 type(_type) {
}

/**
 * @brief Copys a component
 * @param component, copy template for the new component
 * @return position of the new component
 */
Component::Component(const Component &component):position(component.position), normal(component.normal), type(component.type){}
const std::vector<double> &Component::getPosition() {
    return position;
}

/**
 * @brief Standard get-method for getting the current normal of the component
 * @return normal of the component
 */
const std::vector<double> &Component::getNormal() {
    return normal;
}

/**
 * @brief Standard set-method for setting the position of the component
 * @param _position, sets the new position of the photon
 */
void Component::setPosition(std::vector<double> &_position) {
    assert(_position.size() == 3);
    position = _position;
}

/**
 * @brief Standard set-method for setting the normal of the component
 * @param _normal, sets the new normal of the photon
 */
void Component::setNormal(std::vector<double> &_normal) {
    normal = _normal;
}

/**
 * @brief Standard get-method for getting the current type of the component
 * @return type of the current component
 */
const ComponentType &Component::getType() {
    return type;
}
