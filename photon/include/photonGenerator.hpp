#pragma once
#include <unordered_map>
#include <boost/numeric/ublas/vector.hpp>
#include "photon.hpp"
#include "../../utils/include/objectPoint.hpp"
typedef typename boost::numeric::ublas::vector<double> vector;
class PhotonGenerator{
    private:
    //Der Erste Eintrag ist der Oberflaechenpunkt, des Photonen austrahlenden Objektes das zweite die wellenlaenge wenn, die intensitaet auch aus dem object auslesbar
    //ist muss man dieses hier noch erweitern
    objectPoint raster[65536];
    public:
    PhotonGenerator(objectPoint[65536]);
    Photon generatePhoton();
};
