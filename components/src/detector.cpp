#include "detector.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/math/constants/constants.hpp>
#include "../../utils/include/utils.hpp"
#include <cmath>
#include <cstdint>

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename boost::numeric::ublas::vector<RGB> rgb_vector;
typedef typename boost::numeric::ublas::matrix<RGB> rgb_matrix;
typedef typename boost::numeric::ublas::vector<BmpRGB> bmp_vector;

vector Detector::getPosOfPrevComponent() {
    return posOfPrevComponent;
}

void Detector::setPosOfPrevComponent(vector& _pos) {
    posOfPrevComponent = _pos;
}

vector Detector::getPointOnEdge() {
    return pointOnEdge;
}

void Detector::setPointOnEdge(vector& _point) {
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

    vector relativePosition = intersection - position; // Position vom Photon relativ zum Detektormittelpunkt
    vector detectorNormal = posOfPrevComponent - position; // Normalvektor in der Mitte von Detektor
    vector ref = pointOnEdge - position; // Position vom pointOnEdge relativ zum Detektormittelpunkt
    Utils::normalizeVector(detectorNormal);
    double dp = Utils::dot_product(ref, relativePosition);
    vector cp = Utils::cross_product_2(relativePosition, ref);

    // temp hier wiederverwenden zum Speicheroptimierung
    temp = Utils::dot_product(cp, detectorNormal);
    temp = atan2(temp, dp); //Berechnet Winkel in der Ebene zwischen ref und relativePosition in [-pi,+pi]
    double a, b, c;
    c = sqrt(pow(relativePosition(0), 2) + pow(relativePosition(1), 2) + pow(relativePosition(2), 2));
    a = abs(c * sin(temp));

    if (a < length / 2) {
        b = sqrt(c * c - a * a);
        if (b < length / 2) {
            RGB color;
            const int wl = photon.getWaveLength();
            Utils::coreTranslationInColor(wl, color.r, color.g, color.b);
            int i_index = floor(b / pixelSize);
            int j_index = floor(a / pixelSize);
            if (temp >= 0) {
                if (temp < boost::math::constants::pi<double>() / 2) {
                    i_index = floor(size / 2 - i_index);
                    j_index = floor(size / 2 - j_index);

                    sensor(i_index, j_index).addRGB(color);
                    sensor(i_index, j_index).intensity = sensor(i_index, j_index).intensity + 1;
                }
                else {
                    i_index = floor(size / 2 + i_index);
                    j_index = floor(size / 2 - j_index);

                    sensor(i_index, j_index).addRGB(color);
                    sensor(i_index, j_index).intensity = sensor(i_index, j_index).intensity + 1;
                }
            }
            else {
                if (temp > boost::math::constants::pi<double>() / (-2)) {
                    i_index = floor(size / 2 - i_index);
                    j_index = floor(size / 2 + j_index);

                    sensor(i_index, j_index).addRGB(color);
                    sensor(i_index, j_index).intensity = sensor(i_index, j_index).intensity + 1;
                }
                else {
                    i_index = floor(size / 2 + i_index);
                    j_index = floor(size / 2 + j_index);

                    sensor(i_index, j_index).addRGB(color);
                    sensor(i_index, j_index).intensity = sensor(i_index, j_index).intensity + 1;
                }
            }
        }
    }
}

 bmp_vector Detector::createImage() {

    double max = sensor(0, 0).intensity;
    double min = max;
    double avg = 0.0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (sensor(i, j).intensity > max) {
                max = sensor(i, j).intensity;
            } else if (sensor(i, j).intensity < min) {
                min = sensor(i, j).intensity;
            }
            avg += sensor(i, j).intensity;
        }
    }
    avg = avg / (size * size);
    brightness = (avg / max) * 100;

    rgb_vector image (size * size);
    RGB color;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            if (sensor(i, j).intensity == 0) {
                color.r = sensor(i, j).r;
                color.g = sensor(i, j).g;
                color.b = sensor(i, j).b;
            }
            else {
                color.r = sensor(i, j).r / sensor(i, j).intensity;
                color.g = sensor(i, j).g / sensor(i, j).intensity;
                color.b = sensor(i, j).b / sensor(i, j).intensity;
                color.intensity = sensor(i, j).intensity;

            }
            image(j + i * size) = color;
        }
    }

    unsigned const int sz = size - 1;
    vector bw (sz * sz);
    for (int i = 1; i < sz; i++) {
        for(int j = 1; j < sz; j++) {
            bw((j - 1) + (i - 1) * sz) = (image(j + i * sz).intensity * (-4)) + (image(j - 1 + i * sz).intensity) + (image(j + 1 + i * sz).intensity) + (image(j + (i - 1) * sz).intensity) + (image(j + (i + 1) * sz).intensity);
        }
    }

    for (int i = 0; i < sz * sz; i++) {
        if (bw(i) >= sharpness) {
            sharpness = bw(i);
        }
    }
    // Obwohl die Werte auf [0, 100] verteilt sind, bedeuten Werte wie 35 - 40 besonders hohe Schärfe;
    // Dies liegt daran, dass das Bild ganz spezifische Struktur haben muss um Schärfewerte im Bereich [60 - 100] zu erzeugen;
    sharpness = (sharpness / (max * 4)) * 100;

    double adjustment;
    for (int i = 0; i < image.size(); i++) {
        adjustment = (image[i].intensity - avg) * 4.0; // Muss testen wie sinnvoll adjustment berechnet wird. Werte zwischen 1 und 5 scheinen gut zu funktionieren;
        if (image[i].intensity >= avg) {
            image[i].r = std::round(Utils::min(image[i].r + adjustment, 255));
            image[i].g = std::round(Utils::min(image[i].g + adjustment, 255));
            image[i].b = std::round(Utils::min(image[i].b + adjustment, 255));
        }
        else {
            image[i].r = std::round(Utils::max(image[i].r + adjustment, 0));
            image[i].g = std::round(Utils::max(image[i].g + adjustment, 0));
            image[i].b = std::round(Utils::max(image[i].b + adjustment, 0));
        }
    }
    bmp_vector bitmap(size * size);
    for (int i = 0; i < bitmap.size(); i++) {
        bitmap[i].setBmpRGB(image[i]);
    }
    return bitmap;
}

Detector::Detector(vector& _pos, vector& _normal, vector& _pointOnEdge, vector& _posOfPrevComponent, unsigned int _size, double _pixelSize):Detector::Component(_pos, _normal) {
    pointOnEdge = _pointOnEdge;
    posOfPrevComponent = _posOfPrevComponent;
    size = _size;
    pixelSize = _pixelSize;
    length = static_cast<double>(size) * pixelSize;
    brightness = 0;
    sharpness = 0;
    sensor = rgb_matrix (size, size);
}