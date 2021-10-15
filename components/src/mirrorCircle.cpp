#include "mirrorCircle.hpp"

const double &MirrorCircle::getRadius() {
    return getRadiusW();
}
MirrorCircle::MirrorCircle(vector& _pos, vector& _normal, double _radius):MirrorElliptical(_pos,  _normal, _radius, _radius, mirrorCircle){
}