#include "detector.hpp"
#include "../../photon/include/photon.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/math/constants/constants.hpp>
#include <vector>
#include <assert.h>
#include "../include/utils.hpp"
#include "../include/rgb.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename std::vector<RGB> rgb_dynamic_v;
typedef typename boost::numeric::ublas::vector<RGB> rgb_vector;
typedef typename boost::numeric::ublas::matrix<rgb_dynamic_v> photon_matrix;

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

    vector relativePosition = pV - position; // Position vom Photon relativ zum Detektormittelpunkt
    vector detectorNormal = posOfPrevComponent - position; // Normalvektor in der Mitte von Detektor
    vector ref = pointOnEdge - position; // Position vom pointOnEdge relativ zum Detektormittelpunkt
    normalizeVector(detectorNormal);

    // temp hier wiederverwenden zum Speicheroptimierung
    temp = atan2(dot_product(cross_product_2(relativePosition, ref), detectorNormal), dot_product(ref, relativePosition)); //Berechnet Winkel in der Ebene zwischen ref und relativePosition in [-pi,+pi]
    double a, b, c;
    c = sqrt(relativePosition(0)^2 + relativePosition(1)^2 + relativePosition(2)^2);
    a = abs(c * sin(temp));

    if (a < length / 2) {
        b = sqrt(c^2 - a^2);
        if (b < length / 2) {
            RGB color;
            coreTranslationInColor(photon.waveLength, color.r, color.g, color.b);
            int i_index = floor(b / pixelSize);
            int j_index = floor(a / pixelSize);
            if (temp > 0) {
                if (temp < boost::math::constants::pi<double>() / 2) {
                    sensor(size / 2 - i_index, size / 2 - j_index).pushback(color);
                }
                else {
                    sensor(size / 2 + i_index, size / 2 - j_index).pushback(color);
                }
            }
            else {
                if (temp > boost::math::constants::pi<double>() / (-2)) {
                    sensor(size / 2 - i_index, size / 2 + j_index).pushback(color);
                }
                else {
                    sensor(size / 2 + i_index, size / 2 + j_index).pushback(color);
                }
            }
        }
    }
}

 rgb_vector Detector::createImage() {
    rgb_vector image (size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            RGB color;
            for(int k = 0; k < sensor(i,j).size(); k++) {
                color.r += sensor(i,j)[k].r;
                color.g += sensor(i,j)[k].g;
                color.b += sensor(i,j)[k].b;
            }
            color.intensity = sensor(i,j).size();
            color.r = color.r/sensor(i,j).size();
            color.g = color.g/sensor(i,j).size();
            color.b = color.b/sensor(i,j).size();
            image(j + i * size) = color;
        }
    }
    double max = image[0].intensity;
    double min = max;
    double avg = 0;
    for (int i = 0; i < image.size(); i++) {
        if (image[i].intensity > max) {
            max = image[i].intensity;
        }
        else if (image[i].intensity < min) {
            min = image[i].intensity;
        }
        avg += image[i].intensity;
    }
    avg = avg / (image.size());
    double factor = avg / (max - min);
    double adjustment = 0;
    for (int i = 0; i < image.size()) {
        adjustment = (image[i].intensity - avg) * factor; //Muss testen wie sinnvoll adjustment berechnet wird
        image[i].r = image[i].r + adjustment;
        image[i].g = image[i].g + adjustment;
        image[i].b = image[i].b + adjustment;
    }
    return image;
}

Detector::Detector(vector& _pos, vector& _normal, int _size, double _pixelSize, double _length):Detector::Component(_pos, _normal) {
    size = _size;
    pixleSize = _pixelSize;
    length = size * pixelSize;
    sensor = photon_matrix (size, size);
}