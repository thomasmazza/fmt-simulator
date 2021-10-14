#include "component.hpp"
#include <assert.h>

Component::Component(vector &_position, vector &_normal, ComponentType _type) : position(_position), normal(_normal),
                                                                                 type(_type) {
}

const vector &Component::getPosition() {
    return position;
}

const vector &Component::getNormal() {
    return normal;
}

void Component::setPosition(vector &_position) {
    assert(_position.size() == 3);
    position = _position;
}

void Component::setNormal(vector &_normal) {
    normal = _normal;
}

const ComponentType &Component::getType() {
    return type;
}