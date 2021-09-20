#include "SquareMirror.hpp"
SquareMirror::SquareMirror(vector & vector1, vector & vector2, vector & vector3, vector & _position, vector & _normal, double _length):
RectangleMirror(vector1, vector2, vector3, _position, _normal, _length, _length){
    length = _length;
}
