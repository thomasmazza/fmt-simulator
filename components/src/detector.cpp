#include "detector.hpp"
#include "../../photon/include/photon.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename boost::numeric::ublas::vector<*Photon> photonVector;
typedef typename boost::numeric::ublas::matrix<photonVector> photonMatrix;

Detector::Detector(vector& _pos, vector& _normal, int _size, double _pixelSize):Detector::Component(_pos, _normal) {
    size = _size;
    pixleSize = _pixelSize;
    length = size * pixelSize;
}