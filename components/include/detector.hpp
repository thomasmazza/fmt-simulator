#pragma once

#include <vector>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "component.hpp"
#include "../../photon/include/photon.hpp"
#include "rgb.hpp"
#include "bmprgb.hpp"


typedef typename std::vector<RGB> rgb_dynamic_v;//Kann verändert sein, abhängig davon wie die Photon und wie die Wellenlängen zuerst gespeichert werden
typedef typename std::vector<RGB> rgb_vector;
typedef typename std::vector<std::vector<RGB>> rgb_matrix;
typedef typename std::vector<BmpRGB> bmp_vector;


class Detector : public Component {
protected:
    std::vector<double> pointOnEdge; // Punkt in der Mitte der obere Kannte des Detectors. Muss gegeben oder irgendwie bestimmt werden
    std::vector<double> posOfPrevComponent; // vector position von dem vorkommenden Komponenten
    unsigned int size; // Detector hat size * size Pixel
    double pixelSize; //Größe eines Pixels
    double length; // Dimensionen von dem Detektor
    double brightness;
    double sharpness;
    rgb_matrix sensor;
public:

    const std::vector<double>& getPointOnEdge();

    const std::vector<double>& getPosOfPrevComponent();

    const int getSize();

    const double getPixelSize();

    void setPosOfPrevComponent(std::vector<double> &);

    void setPointOnEdge(std::vector<double> &);

    Detector(std::vector<double> &, std::vector<double> &, std::vector<double> &, std::vector<double> &, unsigned int, double);

    void getInPoint(Photon &);

    bmp_vector createImage();
};
