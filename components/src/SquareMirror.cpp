#include "SquareMirror.hpp"

SquareMirror::SquareMirror(vector& _pos, vector& _normal, double _length):RectangleMirror(_pos, _normal, _length, _length){
    length = _length;
}
