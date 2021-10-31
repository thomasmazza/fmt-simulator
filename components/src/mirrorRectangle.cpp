#include "mirrorRectangle.hpp"

#include "../../utils/include/utils.hpp"
#include <cmath>

/**
 * @brief Main function of every component, calculates the position and direction after the photon passes
 * @param photon, Photon who should be calculated
 * @return true, if photon passes the mirror
 */
bool MirrorRectangle::getOutDir(Photon &p, std::vector<double> &_dirOA) {
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
        mHigh = (lengthH/2) * mHigh;
        mWidth = (lengthW/2) * mWidth;


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

        double h = (rS / (pow((lengthH/2), 2)));
        double w = (lS / (pow((lengthW/2), 2)));

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
bool MirrorRectangle::calcOut(Photon &p, std::vector<double> &intersect, std::vector<double> &normWidth) {
    //neuer Stützvektor wird der Schnittpunkt
    p.setPosition(intersect);

    std::vector<double> out(3);
    std::vector<double> dV = p.getDirection();
    double sumVE = 0;

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

    for (int i = 0; i < 3; i++) {
        if(out[i]<0.001)out[i]=0;
    }

    //An Photon übergeben
    p.setDirection(out);

    return true;
}

/**
 * @brief Standard get-method for getting the current lengthH of the mirror
 * @return current lengthH of the lens
 */
const double &MirrorRectangle::getLengthH() {
    return lengthH;
}

/**
 * @brief Standard get-method for getting the current lengthW of the mirror
 * @return current lengthW of the lens
 */
const double &MirrorRectangle::getLengthW() {
    return lengthW;
}

/**
 * @brief Standard set-method for setting a new lengthH for the mirror
 * @param new lengthH for the mirror
 */
void MirrorRectangle::setLengthH(double _lengthH) {
    lengthH = _lengthH;
}

/**
 * @brief Standard set-method for setting a new lengthW for the mirror
 * @param new lengthW for the mirror
 */
void MirrorRectangle::setLengthW(double _lengthW) {
    lengthW = _lengthW;
}

/**
 * @brief Constructs a mirrorRectangle
 * @param _position, sets the position of the new mirrorRectangle
 * @param _normal, sets the normal of the new mirrorRectangle
 * @param _lengthH, sets the lengthH of the new mirrorRectangle
 * @param _lengthW, sets the lengthW of the new mirrorRectangle
 * @param _type, sets the type of the component ("mirrorRectangle")
 */
MirrorRectangle::MirrorRectangle(std::vector<double> &_pos, std::vector<double> &_normal, double _lengthH, double _lengthW): Component(_pos,_normal, mirrorRectangle), lengthH(_lengthH), lengthW(_lengthW) {
}

/**
 * @brief Copys a mirrorRectangle
 * @param mirrorRectangle1, copy template for the new mirrorRectangle
 */
MirrorRectangle::MirrorRectangle(const MirrorRectangle &mirrorRectangle1): Component(mirrorRectangle1), lengthH(mirrorRectangle1.lengthH), lengthW(mirrorRectangle1.lengthW) {}
