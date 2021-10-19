#pragma once

#include <vector>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "component.hpp"
#include "../../photon/include/photon.hpp"
#include "rgb.hpp"
#include "bmprgb.hpp"


typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename std::vector<RGB> rgb_dynamic_v;//Kann verändert sein, abhängig davon wie die Photon und wie die Wellenlängen zuerst gespeichert werden
typedef typename boost::numeric::ublas::vector<RGB> rgb_vector;
typedef typename boost::numeric::ublas::matrix<RGB> rgb_matrix;
typedef typename boost::numeric::ublas::vector<BmpRGB> bmp_vector;


class Detector: public Component {
protected:
    vector pointOnEdge; // Punkt in der Mitte der obere Kannte des Detectors. Muss gegeben oder irgendwie bestimmt werden
    vector posOfPrevComponent; // vector position von dem vorkommenden Komponenten
    unsigned int size; // Detector hat size * size Pixel
    double pixelSize; //Größe eines Pixels
    double length; // Dimensionen von dem Detektor
    double brightness;
    rgb_matrix sensor;
public:
    vector getPosOfPrevComponent();
    void setPosOfPrevComponent(vector&);
    vector getPointOnEdge();
    void setPointOnEdge(vector&);
    Detector(vector&, vector&, vector&, vector &, unsigned int, double);
    void getInPoint(Photon&);
    bmp_vector createImage();
};
