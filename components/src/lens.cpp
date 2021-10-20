#include "../include/lens.hpp"

Lens::Lens(std::vector<double>& _pos, std::vector<double>& _normal, double _radiusH,double _n, double _d, ComponentType _type):Component(_pos, _normal, _type), radiusH(_radiusH), n(_n), d(_d){
}

Lens::Lens(const Lens &lens): Component(lens), radiusH(lens.radiusH), d(lens.d), n(lens.n){}

const double &Lens::getD() {
    return d;
}

const double &Lens::getN(){
    return n;
}

const double &Lens::getRadiusH() {
    return radiusH;
}

void Lens::setN(double _n) {
    n = _n;
}

void Lens::setD(double _d) {
    d = _d;
}

void Lens::setRadiusH(double _radiusH) {
    radiusH = _radiusH;
}