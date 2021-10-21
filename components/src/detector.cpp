#include "../include/detector.hpp"
#include "../../utils/include/utils.hpp"
#include <cmath>



const std::vector<double>& Detector::getPosOfPrevComponent() {
    return posOfPrevComponent;
}

void Detector::setPosOfPrevComponent(std::vector<double> &_pos) {
    posOfPrevComponent = _pos;
}

const std::vector<double>& Detector::getPointOnEdge() {
    return pointOnEdge;
}

const int Detector::getSize() {
    return size;
}

void Detector::setPointOnEdge(std::vector<double> &_point) {
    pointOnEdge = _point;
}

const double Detector::getPixelSize() {
    return pixelSize;
}

void Detector::getInPoint(Photon &photon) {
    std::vector<double> pV = photon.getPosition();
    std::vector<double> dV = photon.getDirection();
    std::vector<double> intersection(3);

    //Berechnet den Schnittpunkt von Photon und Ebene
    double temp = (normal[0] * (position[0] - pV[0]) + normal[1] * (position[1] - pV[1]) +
                   normal[2] * (position[2] - pV[2])) / (normal[0] * dV[0] + normal[1] * dV[1] + normal[2] * dV[2]);
    for (int i = 0; i < 3; i++) {
        intersection[i] = dV[i] * temp + pV[i];
    }

    std::vector<double> relativePosition = intersection - position; // Position vom Photon relativ zum Detektormittelpunkt
    std::vector<double> detectorNormal = posOfPrevComponent - position; // Normalvektor in der Mitte von Detektor
    std::vector<double> ref = pointOnEdge - position; // Position vom pointOnEdge relativ zum Detektormittelpunkt
    Utils::normalizeVector(detectorNormal);
    double dp = Utils::dot_product(ref, relativePosition);
    std::vector<double> cp = Utils::cross_product_2(relativePosition, ref);

    // temp hier wiederverwenden zum Speicheroptimierung
    temp = Utils::dot_product(cp, detectorNormal);
    temp = atan2(temp, dp); //Berechnet Winkel in der Ebene zwischen ref und relativePosition in [-pi,+pi]
    double a, b, c;
    c = sqrt(pow(relativePosition[0], 2) + pow(relativePosition[1], 2) + pow(relativePosition[2], 2));
    a = std::abs(c * sin(temp));

    if (a < length / 2) {
        b = sqrt(c * c - a * a);
        if (b < length / 2) {
            RGB color;
            const int wl = photon.getWaveLength();
            Utils::coreTranslationInColor(wl, color.r, color.g, color.b);
            int i_index = floor(b / pixelSize);
            int j_index = floor(a / pixelSize);
            if (temp >= 0) {
                if (temp < M_PI_2) {
                    i_index = floor(size / 2 - i_index);
                    j_index = floor(size / 2 - j_index);

                    sensor[i_index][j_index].addRGB(color);
                    sensor[i_index][j_index].intensity = sensor[i_index][j_index].intensity + 1;
                } else {
                    i_index = floor(size / 2 + i_index);
                    j_index = floor(size / 2 - j_index);

                    sensor[i_index][j_index].addRGB(color);
                    sensor[i_index][j_index].intensity = sensor[i_index][j_index].intensity + 1;
                }
                std::cout << sensor[i_index][j_index].r << std::endl;
            } else {
                if (temp > -M_PI_2) {
                    i_index = floor(size / 2 - i_index);
                    j_index = floor(size / 2 + j_index);

                    sensor[i_index][j_index].addRGB(color);
                    sensor[i_index][j_index].intensity = sensor[i_index][j_index].intensity + 1;
                } else {
                    i_index = floor(size / 2 + i_index);
                    j_index = floor(size / 2 + j_index);

                    sensor[i_index][j_index].addRGB(color);
                    sensor[i_index][j_index].intensity = sensor[i_index][j_index].intensity + 1;
                }
                std::cout << sensor[i_index][j_index].r << std::endl;
            }
        }
    }
}

bmp_vector Detector::createImage() {
    double max = sensor[0][0].intensity;
    double min = max;
    double avg = 0.0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (sensor[i][j].intensity > max) {
                max = sensor[i][j].intensity;
            } else if (sensor[i][j].intensity < min) {
                min = sensor[i][j].intensity;
            }
            avg += sensor[i][j].intensity;
        }
    }
    avg = avg / (size * size);
    brightness = (avg / max) * 100;


    rgb_vector image(size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            RGB color;
            if (sensor[i][j].intensity == 0) {
                color.r = sensor[i][j].r;
                color.g = sensor[i][j].g;
                color.b = sensor[i][j].b;
            } else {
                color.r = sensor[i][j].r / sensor[i][j].intensity;
                color.g = sensor[i][j].g / sensor[i][j].intensity;
                color.b = sensor[i][j].b / sensor[i][j].intensity;
                color.intensity = sensor[i][j].intensity;
            }
            image[j + i * size] = color;
        }
    }

    unsigned const int sz = size - 1;
    std::vector<double> bw (sz * sz);
    for (int i = 1; i < sz; i++) {
        for(int j = 1; j < sz; j++) {
            bw[(j - 1) + (i - 1) * sz] = (image[j + i * sz].intensity * (-4)) + (image[j - 1 + i * sz].intensity) + (image[j + 1 + i * sz].intensity) + (image[j + (i - 1) * sz].intensity) + (image[j + (i + 1) * sz].intensity);
        }
        avg += image[i].intensity;
    }
    sharpness = 0;
    for (int i = 0; i < sz * sz; i++) {
        if (bw[i] >= sharpness) {
            sharpness = bw[i];
        }
    }
    // Obwohl die Werte auf [0, 100] verteilt sind, bedeuten Werte wie 35 - 40 besonders hohe Schärfe;
    // Dies liegt daran, dass das Bild ganz spezifische Struktur haben muss um Schärfewerte im Bereich [60 - 100] zu erzeugen;
    sharpness = (sharpness / (max * 4)) * 100;

    double adjustment;
    for (int i = 0; i < image.size(); i++) {
        adjustment = (image[i].intensity - avg) * 2.0; //Muss testen wie sinnvoll adjustment berechnet wird
        if (image[i].intensity >= avg) {
            image[i].r = std::round(Utils::min(image[i].r + adjustment, 255));
            image[i].g = std::round(Utils::min(image[i].g + adjustment, 255));
            image[i].b = std::round(Utils::min(image[i].b + adjustment, 255));
        } else {
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

const double & Detector::getBrightness() {
    return brightness;
}

const double & Detector::getSharpness() {
    return sharpness;
}


Detector::Detector(std::vector<double> &_pos, std::vector<double> &_normal, std::vector<double> &_pointOnEdge, std::vector<double> &_posOfPrevComponent, unsigned int _size,
                   double _pixelSize) : Component(_pos, _normal, detector), pointOnEdge(_pointOnEdge),posOfPrevComponent(_posOfPrevComponent),size(_size),pixelSize(_pixelSize), length(_size * _pixelSize),sensor(_size, std::vector<RGB>(_size)) {
}

Detector::Detector(const Detector &detector1): Component(detector1), pointOnEdge(detector1.pointOnEdge), posOfPrevComponent(detector1.posOfPrevComponent), size(detector1.size), pixelSize(detector1.pixelSize) {}
