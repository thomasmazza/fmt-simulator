#include "lens.hpp"
#include <boost/numeric/ublas/vector.hpp>


bool Lens::hitComponent(Photon& p){
    //TODO: Logik einbauen
    return true;
}

Lens::Lens(vector& _pos, vector& _normal, double _n2, double _radiusH, double _d):Lens::Component(_pos, _normal) {
    n2 = _n2;
    radiusH = _radiusH;
    d = _d;
}
