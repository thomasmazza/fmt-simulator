#include "mirror.hpp"
#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;

bool Mirror::hitComponent(Photon& p) {
    //TODO: Logik einbauen
    return true;
}

void Mirror::getOutDir(Photon& p) {
    //TODO: Logik einbauen
}

Mirror::Mirror(vector& _pos, vector& _normal):Mirror::Component(_pos, _normal){
    //TODO: Nothing
}
