#include "lens.hpp"
#include <boost/numeric/ublas/vector.hpp>

Lens::Lens(vector& _pos, vector& _normal, double _n, double _radiusH, double _d):Component(_pos, _normal) {
    n = _n;
    radiusH = _radiusH;
    d = _d;
}
