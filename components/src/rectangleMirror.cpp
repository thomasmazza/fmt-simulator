#include "rectangleMirror.hpp"

RectangleMirror::RectangleMirror(vector& _pos, vector& _normal, double _lengthH, double _lengthW):Mirror(_pos, _normal) {
    lengthH = _lengthH;
    lengthW = _lengthW;
}
