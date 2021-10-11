#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "component.hpp"
#include "../../photon/include/photon.hpp"


typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename boost::numeric::ublas::vector<int> intVector;//Kann verändert sein, abhängig davon wie die Photon und wie die Wellenlängen zuerst gespeichert werden
typedef typename boost::numeric::ublas::matrix<intVector> photon_matrix;

class Detector: public Component {
protected:
    vector pointOnEdge; // Punkt in der Mitte der obere Kannte des Detectors. Muss gegeben oder irgendwie bestimmt werden
    vector posOfPrevComponent; // vector position von dem vorkommenden Komponenten
    int size; // Detector hat size x size Pixel
    double pixelSize;
    double length;
    double halfLength; // Spart die Berechnung von length / 2 bei jeder Aufruf von getInPoint();
    photon_matrix sensor;
public:
    vector getPosOfPrevComponent();
    void setPosOfPrevComponent(vector&);
    vector getPointOnEdge();
    void setPointOnEdge(vector&);
    Detector(vector&, vector&, int, double, double);
    //bool hitComponent(Photon&);
    void getInPoint(Photon&);
    void createImage(photon_matrix&); //Nicht endgueltig
};
