#include "../include/detector.hpp"
#include "../../utils/include/utils.hpp"
#include <cmath>

/**
 * @return Position of the previous component in the list
 */
const std::vector<double>& Detector::getPosOfPrevComponent() {
    return posOfPrevComponent;
}

/**
 * @brief Sets the position of the previous component
 * @param _pos Vector with length 3
 */
void Detector::setPosOfPrevComponent(std::vector<double> &_pos) {
    posOfPrevComponent = _pos;
}

/**
 * @return Number of pixels per row (detector is square)
 */
int Detector::getSize() {
    return size;
}

/**
 * @brief Sets the number of pixels per row
 * @param _size Number of pixels
 */
void Detector::setSize(int _size) {
    size = _size;
}

/**
 * @return Length of detector edge in units of the coordinate system
 */
double Detector::getLength() {
    return length;
}

/**
 * @brief Sets the length of detector
 * @param _length Length of detector
 */
void Detector::setLength(double _length) {
    length = _length;
}

/**
 * @return Size of a single pixel in units of the coordinate system
 */
double Detector::getPixelSize() {
    return pixelSize;
}

/**
 * @brief Sets the size of a single pixel. Used only internally
 * @param _size Number of pixels per row in the detector
 * @param _length Length of detector in coordinate system units
 */
void Detector::setPixelSize(double _size, double _length) {
    pixelSize = _length / _size;
}

/**
 * @brief Calculates which pixel the photon enters and the color information for the pixel
 * @param photon Object from class Photon
 */
void Detector::getInPoint(Photon &photon) {
    std::vector<double> pV = photon.getPosition();
    std::vector<double> dV = photon.getDirection();
    std::vector<double> intersection(3);

    //Berechnet den Schnittpunkt von Photon und Ebene
    double temp = (normal[0] * (position[0] - pV[0]) + normal[1] * (position[1] - pV[1]) +
                   normal[2] * (position[2] - pV[2])) / (normal[0] * dV[0] + normal[1] * dV[1] + normal[2] * dV[2]);

    if(temp>0){
        for (int i = 0; i < 3; i++) {
            intersection[i] = dV[i] * temp + pV[i];
        }
    }else{
        return;
    }

    std::vector<double> relativePosition = intersection - position; // Position vom Photon relativ zum Detektormittelpunkt
    std::vector<double> wid = Utils::cross_product_2(ref, normal);
    Utils::normalizeVector(wid);
    wid = wid*(length/2);

    double xs,ys;
    double a, b, c;
    std::vector<double> x(3);
    std::vector<double> y(3);
    ys = ( (Utils::dot_product(ref, relativePosition)) / pow((length/2), 2) );
    xs = ( (Utils::dot_product(wid, relativePosition)) / pow((length/2), 2) );
    x = xs*wid;
    y = ys*ref;

    if(xs>0){
        xs = Utils::getAbs(x);
    }else{
        xs = Utils::getAbs(x);
        xs = xs*(-1);
    }

    if(ys>0){
        ys = Utils::getAbs(y);
    }else{
        ys = Utils::getAbs(y);
        ys = ys*(-1);
    }

    temp = atan2(ys, xs); //Berechnet Winkel in der Ebene zwischen ref und relativePosition in [-pi,+pi]

    c = sqrt(pow(relativePosition[0], 2) + pow(relativePosition[1], 2) + pow(relativePosition[2], 2));
    a = std::abs(ys);


    if (a < length / 2.0) {
        b = std::abs(xs);
        if (b < length / 2.0) {
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
                //std::cout << "r" << sensor[i_index][j_index].r << " g" << sensor[i_index][j_index].g << " b" << sensor[i_index][j_index].b << std::endl;
                //std::cout << "i " << sensor[i_index][j_index].intensity << std::endl;
            }
        }
    }
}

/**
 * @brief Creates a vector with .bmp-ready values from the data in the detector and calculates brightness and sharpness of the image
 * @return Vector with .bmp-ready RGB values
 */
bmp_vector Detector::createImage() {
    double max = sensor[0][0].intensity;
    double min = max;
    double avg = 0.0;
    double hit = 0.0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (sensor[i][j].intensity > 0) {
                hit += 1.0;
                if (sensor[i][j].intensity > max) {
                    max = sensor[i][j].intensity;
                }
                else if (sensor[i][j].intensity < min) {
                    min = sensor[i][j].intensity;
                }
            }
            avg += sensor[i][j].intensity;
        }
    }
    // avg = avg / ((double)size * (double)size);
    avg = avg / hit;
    brightness = (avg / max) * 100;
    brightness = (100 - brightness);



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
                color.intensity = sensor[i][j].intensity / max;
            }
            image[j + i * size] = color;
        }
    }

    const int sz = size - 1;
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
    sharpness = (4/49)*pow(sharpness, 2) - (40/7)*sharpness +100;

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

/**
 * @return Brightness of the image
 */
const double & Detector::getBrightness() {
    return brightness;
}

/**
 * @return Sharpness of the image
 */
const double & Detector::getSharpness() {
    return sharpness;
}

/**
 * @brief Resets all color values in the detector
 */
void Detector::resetSensor(){
    rgb_matrix emptySensor(size, std::vector<RGB>(size));
    sensor = emptySensor;
}

/**
 * @brief Recalculates detectorNormal and ref attributes of the detector
 */
void Detector::recalculateInternals() {
    detectorNormal = posOfPrevComponent - position;
    ref = { 0, 0, 0}; // ref zuerst nur als Nullvektor

    // Berechnet ref abhängig davon, wie Detektor im Raum positioniert ist
    if (normal[2] != 0) {
        std::vector<double> temp = { 0, 0, 0};
        // Falls der Normalvektor orthogonal zur XY Ebene ist, nehmen wir ref als den x-Einheitsvektor
        if (normal[0] == 0 && normal[1] == 0) {
            ref = { 1, 0, 0 };
        }
        // Falls nicht, berechnen wir ref als die Projektion von der Projektion von dem detectorNormal auf der XY Ebene
        else {
            temp = { 0, 0, 1};
            double coef = Utils::dot_product(detectorNormal, temp);
            temp[2] = coef;
            std::vector<double> projection = detectorNormal - temp;

            projection[0] = - projection[0];
            projection[1] = - projection[1];
            projection[2] = - projection[2];

            coef = Utils::dot_product(projection, detectorNormal) / sqrt(pow(Utils::dot_product(detectorNormal, detectorNormal), 2));
            temp[0] = detectorNormal[0]  * coef;
            temp[1] = detectorNormal[1]  * coef;
            temp[2] = detectorNormal[2]  * coef;
            ref = projection - temp;
            Utils::normalizeVector(ref);
        }
    }
    // In dem Fall dass die Z-Komponente von normal 0 ist, ist der Detektor vertikal im Raum und
    // die Drehung um die Z-Achse spielt keine Role für ref, daher ist ref der z-Einheitsvektor
    else {
        ref = { 0, 0, 1};
    }
    ref = ref * (length / 2.0);
    Utils::normalizeVector(detectorNormal);
}

/**
 * @brief Constructor
 * @param _pos Position vector
 * @param _normal Vector normal to detector plane
 * @param _posOfPrevComponent Position vector of the previous component
 * @param _size Number of pixels per row (detector is square)
 * @param _edgeLength Length of detector in coordinate system units
 */
Detector::Detector(std::vector<double> &_pos, std::vector<double> &_normal, std::vector<double> &_posOfPrevComponent, int _size,
                   double _edgeLength) : Component(_pos, _normal, detector), posOfPrevComponent(_posOfPrevComponent),size(_size),length(_edgeLength),pixelSize(length / (static_cast<double>(size))),sensor(_size, std::vector<RGB>(_size)) {

    detectorNormal = posOfPrevComponent - position;
    ref = { 0, 0, 0}; // ref zuerst nur als Nullvektor

    // Berechnet ref abhängig davon, wie Detektor im Raum positioniert ist
    if (normal[2] != 0) {
        std::vector<double> temp = { 0, 0, 0};
        // Falls der Normalvektor orthogonal zur XY Ebene ist, nehmen wir ref als den x-Einheitsvektor
        if (normal[0] == 0 && normal[1] == 0) {
            ref = { 1, 0, 0 };
        }
        // Falls nicht, berechnen wir ref als die Projektion von der Projektion von dem detectorNormal auf der XY Ebene
        else {
            temp = { 0, 0, 1};
            double coef = Utils::dot_product(detectorNormal, temp);
            temp[2] = coef;
            std::vector<double> projection = detectorNormal - temp;

            projection[0] = - projection[0];
            projection[1] = - projection[1];
            projection[2] = - projection[2];

            coef = Utils::dot_product(projection, detectorNormal) / sqrt(pow(Utils::dot_product(detectorNormal, detectorNormal), 2));
            temp[0] = detectorNormal[0]  * coef;
            temp[1] = detectorNormal[1]  * coef;
            temp[2] = detectorNormal[2]  * coef;
            ref = projection - temp;
            Utils::normalizeVector(ref);
        }
    }
    // In dem Fall dass die Z-Komponente von normal 0 ist, ist der Detektor vertikal im Raum und
    // die Drehung um die Z-Achse spielt keine Role für ref, daher ist ref der z-Einheitsvektor
    else {
        ref = { 0, 0, 1};
    }
    ref = ref * (length / 2.0);
    Utils::normalizeVector(detectorNormal);
}

/**
 * @brief Copy constructor
 * @param detector1 Another detector object
 */
Detector::Detector(const Detector &detector1): Component(detector1), detectorNormal(detector1.detectorNormal), posOfPrevComponent(detector1.posOfPrevComponent), ref(detector1.ref),  size(detector1.size), pixelSize(detector1.pixelSize), length(detector1.length), sensor(detector1.sensor) {}

