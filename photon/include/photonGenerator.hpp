#pragma once
#include <unordered_map>
#include <boost/numeric/ublas/vector.hpp>
#include "photon.hpp"
#include "../../utils/include/objectPoint.hpp"
class PhotonGenerator{
private:
    //Der Erste Eintrag ist der Oberflaechenpunkt, des Photonen austrahlenden Objektes das zweite die wellenlaenge wenn, die intensitaet auch aus dem object auslesbar
    //ist muss man dieses hier noch erweitern
    std::vector<objectPoint> raster;
public:
    PhotonGenerator(std::vector<objectPoint>);
    Photon generatePhoton();
};
