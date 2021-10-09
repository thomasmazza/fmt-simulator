#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "component.hpp"
#include "../../photon/include/photon.hpp"


typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename boost::numeric::ublas::vector<int> intVector;//Kann verändert sein, abhängig davon wie die Photon und wie die Wellenlängen zuerst gespeichert werden
typedef typename boost::numeric::ublas::matrix<intVector> photonMatrix;

class Detector: public Component {
protected:
    vector pointOnEdge; // Punkt in der Mitte der obere Kannte des Detectors. Muss gegeben oder irgendwie bestimmt werden
    vector posOfPrevComponent; // vector position von dem vorkommenden Komponenten
    int numberOfPixels;
    double pixelSize;
    double length;
    photonMatrix sensor;
public:
    vector getPosOfPrevComponent();
    void setPosOfPrevComponent(vector&);
    vector getPointOnEdge();
    void setPointOnEdge(vector&);
    Detector(vector&, vector&, int, double, double);
    //bool hitComponent(Photon&);
    vector getInPoint(Photon&);
};
