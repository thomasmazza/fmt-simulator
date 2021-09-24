#include "../include/lensTwoSided.hpp"
#include <boost/numeric/ublas/vector.hpp>


void LensTwoSided::getOutDir(photon& p){
    //TODO: Logik einbauen
}

std::string LensTwoSided::getType() {
    return "LensTwoSided";
}

double LensTwoSided::getRadiusI() {
    return radiusI;
}

double LensTwoSided::getRadiusO() {
    return radiusO;
}

LensTwoSided::LensTwoSided(vector& _pos, vector& _normal, double _refIndex, double _radiusH, double _radiusI, double _radiusO)
:LensTwoSided::Lens(_pos, _normal, _refIndex, _radiusH) {
    radiusI = _radiusI;
    radiusO = _radiusO;
}
