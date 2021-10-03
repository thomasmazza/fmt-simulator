#include "detector.hpp"
#include "../../photon/include/photon.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>


typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename std::vector<*Photon> photonVector;
typedef typename boost::numeric::ublas::matrix<photonVector> photonMatrix;


vector Detector::getInPoint(Photon& photon) {
    vector pV = photon.getPosition();
    vector dV = photon.getDirection();
    vector intersection(3);
    //Berechnet den Punkt wo das Photon die Ebene des Detectors trifft
    double temp = (normal[0] * (position[0] - pV[0]) + normal[1] * (position[1] - pV[1]) + normal[2] * (position[2] - pV[2])) / (normal[0] * dV[0] + normal[1] * dV[1] + normal[2] * dV[2]);
    for (int i = 0; i < 3; i++){
        intersection[i] = dV[i] * temp + pV[i];

    }
    //TODO: Überprüfe ob das Photon im Rahmen des Sensors ist, und berechne in welchem Pixel. Hängt davon ab, wie wir das Koordinatesystem definieren (Morgen)
}
Detector::Detector(vector& _pos, vector& _normal, int _size, double _pixelSize, double _length):Detector::Component(_pos, _normal) {
    size = _size;
    pixleSize = _pixelSize;
    length = size * pixelSize;
    sensor = photonMatrix (size, size);
}