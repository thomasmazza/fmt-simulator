#include "../include/mirrorSquare.hpp"

std::string MirrorSquare::getType() {
    return "MirrorSquare";
}

MirrorSquare::MirrorSquare(vector& _pos, vector& _normal, double _length):MirrorRectangle(_pos, _normal, _length, _length){
}