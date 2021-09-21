#include "circleMirror.hpp"

CircleMirror::CircleMirror(vector& _pos, vector& _normal, double _radius):Mirror(_pos, _normal){
    radius = _radius;
}
