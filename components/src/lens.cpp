#include "../include/lens.hpp"
#include <boost/numeric/ublas/vector.hpp>


bool Lens::hitComponent(Photon& p){
    //TODO: Logik einbauen
    return true;
}

double Lens::getRefIndex() {
    return refIndex;
}

double Lens::getRadiusH() {
    return radiusH;
}

Lens::Lens(vector& _pos, vector& _normal, double _refIndex, double _radiusH):Lens::Component(_pos, _normal) {
    refIndex = _refIndex;
    radiusH = _radiusH;
}
