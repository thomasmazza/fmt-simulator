#include "rectangleMirror.hpp"

RectangleMirror::RectangleMirror(vector & vector1, vector & vector2, vector & vector3, vector & position, vector & normal, double _lengthH, double _lengthW):
Mirror(vector1, vector2, vector3, position, normal) {
    lengthW = _lengthW;
    lengthH = _lengthH;
}