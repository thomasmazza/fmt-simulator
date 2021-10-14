#include "mirrorSquare.hpp"
#include "mirrorRectangle.hpp"

MirrorSquare::MirrorSquare(vector& _pos, vector& _normal, double _length):MirrorRectangle(_pos, _normal, _length, _length, mirrorCircle){
}