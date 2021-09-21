#include "ellipticalMirror.hpp"

EllipticalMirror::EllipticalMirror(vector& pos, vector& _normal, double _rH, double _rW):Mirror(pos, _normal) {
    rH= _rH;
    rW= _rW;
}
