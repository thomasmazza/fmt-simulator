#include "../include/mirrorSquare.hpp"

std::string MirrorSquare::getType() {
    return "MirrorSquare";
}

const double &MirrorSquare::getLength() {
    return getLengthW();
}
MirrorSquare::MirrorSquare(std::vector<double>& _pos, std::vector<double>& _normal, double _length):MirrorRectangle(_pos, _normal, _length, _length, mirrorCircle){
}

MirrorSquare::MirrorSquare(const MirrorSquare &mirrorSquare1): MirrorRectangle(mirrorSquare1) {}