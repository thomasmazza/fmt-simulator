#include "lensOneSided.hpp"
#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;

void LensOneSided::getOutDir(photon& p){
    //TODO: Logik einbauen
}

LensOneSided::LensOneSided(vector& _pos, vector& _normal, double _refIndex, double _radiusH, double _radiusW, bool _planeIsFront)
:LensOneSided::Lens(_pos, _normal, _refIndex, _radiusH) {
    radiusW = _radiusW;
    planeIsFront = _planeIsFront;
}
