#include "../include/mirrorCircle.hpp"

std::string MirrorCircle::getType() {
    return "MirrorCircle";
}

const double MirrorCircle::getRadius() {
    return getRadiusW();
}
MirrorCircle::MirrorCircle(std::vector<double>& _pos, std::vector<double>& _normal, double _radius):MirrorElliptical(_pos,  _normal, _radius, _radius, mirrorCircle){
}