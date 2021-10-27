#pragma once

#include <vector>
#include "component.hpp"
#include "../../photon/include/photon.hpp"
#include "../../utils/include/rgb.hpp"
#include "../../utils/include/bmprgb.hpp"


typedef typename std::vector<RGB> rgb_dynamic_v;//Kann verändert sein, abhängig davon wie die Photon und wie die Wellenlängen zuerst gespeichert werden
typedef typename std::vector<RGB> rgb_vector;
typedef typename std::vector<std::vector<RGB>> rgb_matrix;
typedef typename std::vector<BmpRGB> bmp_vector;


class Detector : public Component {
protected:
    std::vector<double> detectorNormal;
    std::vector<double> posOfPrevComponent; // vector position von dem vorkommenden Komponenten
    std::vector<double> ref;
    unsigned int size; // Detector hat size * size Pixel
    double pixelSize; //Größe eines Pixels
    double length; // Dimensionen von dem Detektor
    double brightness;
    double sharpness;
    rgb_matrix sensor;
public:

    const std::vector<double>& getPosOfPrevComponent();

    int getSize();

    double getPixelSize();

    void setPosOfPrevComponent(std::vector<double> &);

    Detector(std::vector<double> &, std::vector<double> &, std::vector<double> &, unsigned int, double);

    Detector(const Detector& detector1);

    void getInPoint(Photon &);

    bmp_vector createImage();

    const double & getBrightness();

    const double & getSharpness();

};
