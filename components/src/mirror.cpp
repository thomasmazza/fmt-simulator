#include "mirror.hpp"
#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;

bool Mirror::hitComponent(vector Position) {
    //TODO: Logik einbauen
    return true;
}

vector Mirror::getOutDir(vector& r, vector& p) {
    //TODO: Logik einbauen
    return r;
}

Mirror::Mirror(vector& vector1, vector& vector2, vector& vector3, vector& _position, vector& _normal):
Mirror::Component(position, normal){
    plane[0]= vector1;
    plane[1]= vector2;
    plane[2]= vector3;
}