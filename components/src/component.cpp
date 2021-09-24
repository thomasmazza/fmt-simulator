#include "../include/component.hpp"
#include <assert.h>
typedef typename boost::numeric::ublas::vector<double> vector;
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

/*
    template<typename T>
    vector<T>& Component<T>::getPos(){
        return pos;
    }

    template<typename T>
    void Component<T>::setPos(vector<T>& _pos){
        pos=_pos;
    }

    template<typename T>
    vector<T>& Component<T>::getNormal(){
        return normal;
    }

    template<typename T>
    void Component<T>::setNormal(vector<T>& _normal){
        normal=_normal;
    }

    template<typename T>
    Component<T>::Component(vector<T>& _pos,vector<T>& _normal):
        pos(_pos),
        normal(_normal){
    }
}*/