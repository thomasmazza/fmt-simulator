#include "../include/component.hpp"
#include <assert.h>

Component::Component(vector& position, vector& normal) {
    setPosition(position);
    setNormal(normal);
}

 vector Component::getPosition() {
    return position;
}

vector Component::getNormal() {
    return  normal;
}

void Component::setPosition(vector& _position) {
    assert(_position.size()==3);
    position = _position;
}

void Component::setNormal(vector& _normal) {
    normal = _normal;
}