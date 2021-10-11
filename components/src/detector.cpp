#include "detector.hpp"
#include "../../photon/include/photon.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/math/constants/constants.hpp>
#include <vector>
#include <assert.h>
#include "utils.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename std::vector<int> intVector;
typedef typename boost::numeric::ublas::matrix<intVector> photon_matrix;

vector Detector::getPosOfPrevComponent() {
    return posOfPrevComponent;
}

void Detector::setPosOfPrevComponent(vector& _pos) {
    assert(_pos.size() == 3);
    posOfPrevComponent = _pos;
}

vector Detector::getPointOnEdge() {
    return pointOnEdge;
}

void Detector::setPointOnEdge(vector& _point) {
    assert(_point.size()==3);
    pointOnEdge = _point;
}

void Detector::getInPoint(Photon& photon) {
    vector pV = photon.getPosition();
    vector dV = photon.getDirection();
    vector intersection(3);
    //Berechnet den Schnittpunkt von Photon und Ebene
    double temp = (normal[0] * (position[0] - pV[0]) + normal[1] * (position[1] - pV[1]) + normal[2] * (position[2] - pV[2])) / (normal[0] * dV[0] + normal[1] * dV[1] + normal[2] * dV[2]);
    for (int i = 0; i < 3; i++){
        intersection[i] = dV[i] * temp + pV[i];
    }
    //TODO: Überprüfe ob das Photon im Rahmen des Sensors ist, und berechne in welchem Pixel. Hängt davon ab, wie wir das Koordinatesystem definieren (Morgen)
    vector relativePosition = pV - position; // Position vom Photon relativ zum Detektormittelpunkt
    vector detectorNormal = posOfPrevComponent - position; // Normalvektor in der Mitte von Detektor
    vector ref = pointOnEdge - position; //
    normalize(detectorNormal);
    // temp hier wiederverwenden zum Speicheroptimierung
    temp = atan2(dot_product(cross_product_2(relativePosition, ref), detectorNormal), dot_product(ref, relativePosition));
    double a, b, c;
    c = sqrt(relativePosition(0)^2 + relativePosition(1)^2 + relativePosition(2)^2);
    a = abs(c * sin(temp));

    if (a < length / 2) {
        b = sqrt(c^2 - a^2);
        if (b < length / 2) {
            int i_index = floor(b / pixelSize);
            int j_index = floor(a / pixelSize);
            if (temp > 0) {
                if (temp < boost::math::constants::pi<double>() / 2) {
                    sensor(size / 2 - i_index, size / 2 - j_index).pushback(photon.waveLength);
                }
                else {
                    sensor(size / 2 + i_index, size / 2 - j_index).pushback(photon.waveLength);
                }
            }
            else {
                if (temp > boost::math::constants::pi<double>() / (-2)) {
                    sensor(size / 2 - i_index, size / 2 + j_index).pushback(photon.waveLength);
                }
                else {
                    sensor(size / 2 + i_index, size / 2 + j_index).pushback(photon.waveLength);
                }
            }
        }
    }
}

void Detector::createImage(photon_matrix&) {

}

Detector::Detector(vector& _pos, vector& _normal, int _size, double _pixelSize, double _length):Detector::Component(_pos, _normal) {
    size = _size;
    pixleSize = _pixelSize;
    length = size * pixelSize;
    halfLength = length / 2;
    sensor = photon_matrix (size, size);
}