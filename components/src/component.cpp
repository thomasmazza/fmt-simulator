#include "component.hpp"
#include <assert.h>

Component::Component(std::vector<double> &_position, std::vector<double> &_normal, ComponentType _type) : position(_position), normal(_normal),
                                                                                 type(_type) {
}

const std::vector<double> &Component::getPosition() {
    return position;
}

const std::vector<double> &Component::getNormal() {
    return normal;
}

void Component::setPosition(std::vector<double> &_position) {
    assert(_position.size() == 3);
    position = _position;
}

void Component::setNormal(std::vector<double> &_normal) {
    normal = _normal;
}

const ComponentType &Component::getType() {
    return type;
}