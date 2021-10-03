#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "component.hpp"
#include "../../photon/include/photon.hpp"


typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename boost::numeric::ublas::vector<*Photon> photonVector;//Kann verändert sein, abhängig davon wie die Photon zuerst gespeichert werden
typedef typename boost::numeric::ublas::matrix<photonVector> photonMatrix;

class Detector: public Component {
protected:
    int size;
    double pixelSize;
    double length;
    photonMatrix sensor;
public:
    Detector(vector&, vector&, int, double, double);
    //bool hitComponent(Photon&);
    vector getInPoint(Photon&);
};
