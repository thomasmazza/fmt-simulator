#pragma once

#include <vector>
#include "component.hpp"
#include "../../photon/include/photon.hpp"
#include "../../utils/include/rgb.hpp"
#include "../../utils/include/bmprgb.hpp"


typedef typename std::vector<RGB> rgb_dynamic_v;
typedef typename std::vector<RGB> rgb_vector;
typedef typename std::vector<std::vector<RGB>> rgb_matrix;
typedef typename std::vector<BmpRGB> bmp_vector;


class Detector : public Component {
protected:
    std::vector<double> detectorNormal; // Vektor aus dem Detektormittelpunkt, orthogonal zur Detektorebene
    std::vector<double> posOfPrevComponent; // vector position von dem vorkommenden Komponenten
    // ref ist Referenzvektor im Detektor zur Berechnung welchen Pixel ein Photon trifft.
    // Im Koordinatensystem mit Nullpunkt die Mitte des Detektors ist ref immer orthogonal
    // zu detectorNormal (also liegt in der Detektorebene)
    // und parallel zu zwei Seiten des Detektors
    std::vector<double> ref;
    int size; // Detector hat size * size Pixel
    double length; // Dimensionen von dem Detektor
    double pixelSize; //Größe eines Pixels
    double brightness;
    double sharpness;
    rgb_matrix sensor;
public:

    const std::vector<double>& getPosOfPrevComponent();

    int getSize();

    void setSize(int);

    double getLength();

    void setLength(double);

    double getPixelSize();

    void setPixelSize(double, double);

    void setPosOfPrevComponent(std::vector<double> &);

    Detector(std::vector<double> &, std::vector<double> &, std::vector<double> &, int, double);

    Detector(const Detector& detector1);

    void getInPoint(Photon &);

    void recalculateInternals();

    bmp_vector createImage();

    const double & getBrightness();

    const double & getSharpness();

    void resetSensor();

};

