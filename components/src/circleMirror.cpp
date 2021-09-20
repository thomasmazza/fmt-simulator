
#include "circleMirror.hpp"

CircleMirror::CircleMirror(vector& vector1, vector& vector2, vector& vector3, vector& _position, vector& _normal, double _radius):
EllipticalMirror(vector1, vector2, vector3, _position, _normal, _radius, _radius){
    radius = _radius;
}
