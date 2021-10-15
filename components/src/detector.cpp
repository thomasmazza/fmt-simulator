#include "detector.hpp"
#include "../../photon/include/photon.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/math/constants/constants.hpp>
#include <vector>
#include <assert.h>
#include "../include/utils.hpp"
#include "../include/pixel.hpp"
#include "../include/rgb.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename std::vector<RGB> rgb_dynamic_v;
typedef typename boost::numeric::ublas::vector<RGB> rgb_vector;
typedef typename boost::numeric::ublas::matrix<Pixel> pixel_matrix;

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
    //assert(_point.size()==3);
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


std::cout << "Intersection " << intersection[0] << "   " << intersection[1] << "   " << intersection [2] << std::endl;


    vector relativePosition = intersection - position; // Position vom Photon relativ zum Detektormittelpunkt

        std::cout << "RelativePosition = " << relativePosition(0) << "  " << relativePosition(1) << "  " << relativePosition(2) << "  " << std::endl;

    vector detectorNormal = posOfPrevComponent - position; // Normalvektor in der Mitte von Detektor

        std::cout << " DN " << detectorNormal[0] <<"  " << detectorNormal[1] <<"  " << detectorNormal[2] << std::endl;

    vector ref = pointOnEdge - position; // Position vom pointOnEdge relativ zum Detektormittelpunkt

    std::cout << " Ref = " << ref[0] << "  " << ref[1] << "  " << ref[2] << std::endl;

    Utils::normalizeVector(detectorNormal);

    std::cout << " normiert DN " << detectorNormal[0] <<"  " << detectorNormal[1] <<"  " << detectorNormal[2] << std::endl;

    double dp = Utils::dot_product(ref, relativePosition);
    std::cout << " DP  " << dp << std::endl;

    vector cp = Utils::cross_product_2(relativePosition, ref);

    std::cout << " CP " << cp[0] << "  " << cp[1] << "  " << cp[2] << std::endl;

    // temp hier wiederverwenden zum Speicheroptimierung
    temp = Utils::dot_product(cp, detectorNormal);

    std::cout << " temp  " << temp << std::endl;

    temp = atan2(temp, dp); //Berechnet Winkel in der Ebene zwischen ref und relativePosition in [-pi,+pi]

    std::cout << "Angle" << temp << std::endl;

    double a, b, c;
    c = sqrt(pow(relativePosition(0), 2) + pow(relativePosition(1), 2) + pow(relativePosition(2), 2));
    std::cout << "c = " << c <<std::endl;
    a = abs(c * sin(temp));
    std::cout << "a = " << a << std::endl;

    if (a <= length / 2) {
        b = sqrt(c * c - a * a);
        std::cout << "b = " << b << std::endl;

        if (b <= length / 2) {
            RGB color;
            const int wl = photon.getWaveLength();
            std::cout << " WL = " << wl << std::endl;
            Utils::coreTranslationInColor(wl, color.r, color.g, color.b);
            int i_index = floor(b / pixelSize);
            std::cout <<  "i = " << i_index << std::endl;

            int j_index = floor(a / pixelSize);
            std::cout <<  "j = " << j_index << std::endl;

            if (temp > 0) {
                if (temp < boost::math::constants::pi<double>() / 2) {
                    i_index = floor(size / 2 - i_index);
                    j_index = floor(size / 2 - j_index);
                    std::cout <<  "i = " << i_index << std::endl;
                    std::cout <<  "j = " << j_index << std::endl;
                    sensor(i_index, j_index).bucket.push_back(color);
                }
                else {
                    i_index = floor(size / 2 + i_index);
                    j_index = floor(size / 2 - j_index);
                    std::cout <<  "i = " << i_index << std::endl;
                    std::cout <<  "j = " << j_index << std::endl;
                    sensor(i_index, j_index).bucket.push_back(color);
                }
            }
            else {
                if (temp > boost::math::constants::pi<double>() / (-2)) {
                    i_index = floor(size / 2 - i_index);
                    j_index = floor(size / 2 + j_index);
                    std::cout <<  "i = " << i_index << std::endl;
                    std::cout <<  "j = " << j_index << std::endl;
                    sensor(i_index, j_index).bucket.push_back(color);
                }
                else {
                    i_index = floor(size / 2 + i_index);
                    j_index = floor(size / 2 + j_index);
                    std::cout <<  "i = " << i_index << std::endl;
                    std::cout <<  "j = " << j_index << std::endl;
                    sensor(i_index, j_index).bucket.push_back(color);
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
            for(int k = 0; k < sensor(i, j).bucket.size(); k++) {
                color.r += sensor(i, j).bucket[k].r;
                color.g += sensor(i, j).bucket[k].g;
                color.b += sensor(i, j).bucket[k].b;
            }
            color.intensity = sensor(i, j).bucket.size();
            color.r = color.r/sensor(i, j).bucket.size();
            color.g = color.g/sensor(i, j).bucket.size();
            color.b = color.b/sensor(i, j).bucket.size();
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
    double adjustment;
    for (int i = 0; i < image.size(); i++) {
        adjustment = (image[i].intensity - avg) * factor; //Muss testen wie sinnvoll adjustment berechnet wird
        if (image[i].intensity >= avg) {
            image[i].r = Utils::min(image[i].r + adjustment, 255);
            image[i].g = Utils::min(image[i].g + adjustment, 255);
            image[i].b = Utils::min(image[i].b + adjustment, 255);
        }
        else {
            image[i].r = Utils::max(image[i].r + adjustment, 0);
            image[i].g = Utils::max(image[i].g + adjustment, 0);
            image[i].b = Utils::max(image[i].b + adjustment, 0);
        }
    }
    return image;
}

Detector::Detector(vector& _pos, vector& _normal, vector& _pointOnEdge, vector& _posOfPrevComponent, double _size, double _pixelSize):Detector::Component(_pos, _normal) {
    pointOnEdge = _pointOnEdge;
    posOfPrevComponent = _posOfPrevComponent;
    size = _size;
    pixelSize = _pixelSize;
    length = static_cast<double>(size) * pixelSize;
    sensor = pixel_matrix (size, size);
    Pixel pix;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sensor(i, j) = pix;
        }
    }
}