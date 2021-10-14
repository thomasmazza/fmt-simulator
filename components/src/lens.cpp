#include "lens.hpp"
#include <boost/numeric/ublas/vector.hpp>

Lens::Lens(vector& _pos, vector& _normal, double _radiusH,double _n, double _d, ComponentType _type):Component(_pos, _normal, _type), radiusH(_radiusH), n(_n) d(_d){
}

const double &Lens::getD() {
    return d;
}

const double &Lens::getN(){
    return n;
}

const double &Lens::getRadiusH() {
    return radiusH;
}
