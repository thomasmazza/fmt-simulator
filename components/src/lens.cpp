#include "lens.hpp"
#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;

bool Lens::hitComponent(Photon& p){
    //TODO: Logik einbauen
    return true;
}

Lens::Lens(vector& _pos, vector& _normal, double _refIndex, double _radiusH):Lens::Component(_pos, _normal) {
    refIndex = _refIndex;
    radiusH = _radiusH;
}
