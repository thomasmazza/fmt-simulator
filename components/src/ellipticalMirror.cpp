#include "ellipticalMirror.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

EllipticalMirror::EllipticalMirror(vector& vector1, vector& vector2, vector& vector3, vector& _position, vector& _normal, double _rH, double _rB):
Mirror(vector1, vector2, vector3, _position, _normal) {
    rH= _rH;
    rB= _rB;
}
