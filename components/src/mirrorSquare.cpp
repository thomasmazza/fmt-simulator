#include "../include/mirrorSquare.hpp"

#include "../../utils/include/utils.hpp"
#include <cmath>

/**
 * @brief Standard get-method for getting the current type of the component
 * @return type of the current component ("MirrorSquare")
 */
std::string MirrorSquare::getType() {
    return "MirrorSquare";
}

/**
 * @brief Standard get-method for getting the current length of the mirror
 * @return current length of the lens
 */
const double &MirrorSquare::getLength() {
    return length;
}

/**
 * @brief Main function of every component, calculates the position and direction after the photon passes
 * @param photon, Photon who should be calculated
 * @return true, if photon passes the mirror
 */
bool MirrorSquare::getOutDir(Photon &p, std::vector<double> &_dirOA) {
    double rS = 0;
    double lS = 0;
    std::vector<double> pV = p.getPosition();
    std::vector<double> dV = p.getDirection();

    //Improvisierte Skalarprodukte
    for (int i = 0; i < 3; i++) {
        rS += normal[i] * (position[i] - pV[i]);
        lS += normal[i] * dV[i];
    }
    bool isComponentHit = false;
    double t = rS / lS;

    //Existiert ein sinnvoller Schnittpunkt oder annähernd Parallel zw. Ebene und Gerade?
    if (t>0) {

        std::vector<double> intersect(3);
        //Berechne den Schnittpunkt
        for (int i = 0; i < 3; i++) {
            intersect[i] = pV[i] + t * dV[i];
        }

        //Überprüfen ob im Bereich, Erst Bereich definieren
        std::vector<double> mHigh(3);
        std::vector<double> mWidth(3);
        Utils::cross_product(mWidth, normal, _dirOA);
        Utils::normalizeVector(mWidth);
        Utils::cross_product(mHigh, mWidth, normal);
        Utils::normalizeVector(mHigh);

        std::vector<double> normWidth = mWidth;

        //Vektor auf Höhe Skalieren
        mHigh = (length/2) * mHigh;
        mWidth = (length/2) * mWidth;


        //Vektor von Mittelpunkt zum Intersect erstellen
        std::vector<double> intPos = intersect - position;

        //lS und rS wiederverwenden zur Speicheroptimierung
        rS = 0;
        lS = 0;

        //Überprüfen ob in Grenze
        for (int i = 0; i < 3; i++) {
            rS += intPos[i] * mHigh[i];
            lS += intPos[i] * mWidth[i];
        }

        double h = (rS / (pow((length/2), 2)));
        double w = (lS / (pow((length/2), 2)));

        //Falls Werte kleiner 1 ist der Betrag entlang der Achsen kleiner als die Ausdehnung => in Grenzen
        if ((h<=1 && h>=-1) && (w<=1 && w>=-1) && calcOut(p, intersect, normWidth)) {
            isComponentHit = true;
        }
    }
    return isComponentHit;
}

/**
 * @brief Outsources calculation for direction of photon
 * @param p, photon who should be calculated
 * @param intersect, intersection vector
 * @param normWidth, normalized vector in direction of the Width
 * @return true, if calculation is done
 */
bool MirrorSquare::calcOut(Photon &p, std::vector<double> &intersect, std::vector<double> &normWidth) {
    //neuer Stützvektor wird der Schnittpunkt
    p.setPosition(intersect);

    std::vector<double> out(3);
    std::vector<double> dV = p.getDirection();
    double sumVE = 0;
    double sumVN = 0;

    //normierter Einfallsvektor berechnen
    for (int i = 0; i < 3; i++) {
        sumVE += pow(dV[i], 2);
    }
    sumVE = sqrt(sumVE);
    for (int i = 0; i < 3; i++) {
        dV[i] /= sumVE;
    }

    //Skalarprodukt aus Einfallsvektor & einer Achse (normiert)
    double coalpha = 0;
    for (int i = 0; i < 3; i++) {
        coalpha += dV[i] * normal[i];
    }

    //Überprüfen ob der Winkel über 90 Grad
    if (coalpha > M_PI_2) {
        coalpha = coalpha - M_PI_2;
    }

    //In Formel einsetzen
    out = dV + (-2*(coalpha*(normal)));

    //An Photon übergeben
    p.setDirection(out);

    return true;
}

/**
 * @brief Standard set-method for setting a new length for the mirror
 * @param new length for the mirror
 */
void MirrorSquare::setLength(double _length) {
    length = _length;
}

/**
 * @brief Constructs a mirrorSquare
 * @param _position, sets the position of the new mirrorSquare
 * @param _normal, sets the normal of the new mirrorSquare
 * @param _length, sets the length of the new mirrorSquare
 * @param _type, sets the type of the component ("mirrorSquare")
 */
MirrorSquare::MirrorSquare(std::vector<double>& _pos, std::vector<double>& _normal, double _length):Component(_pos, _normal, mirrorSquare), length(_length){
}

/**
 * @brief Copys a mirrorSquare
 * @param mirrorSquare1, copy template for the new mirrorSquare
 */
MirrorSquare::MirrorSquare(const MirrorSquare &mirrorSquare1): Component(mirrorSquare1), length(mirrorSquare1.length) {}
