#include "../include/mirrorElliptical.hpp"

#include "../../utils/include/utils.hpp"
#include <cmath>

/**
 * @brief Main function of every component, calculates the position and direction after the photon passes
 * @param photon, Photon who should be calculated
 * @return true, if photon passes the mirror
 */
bool MirrorElliptical::getOutDir(Photon& photon, std::vector<double>& _dirOA) {
    double rS=0;
    double lS=0;
    std::vector<double> pV = photon.getPosition();
    std::vector<double> dV = photon.getDirection();

    //Improvisierte Skalarprodukte
    for(int i=0; i<3; i++){
        rS += normal[i]*(position[i]-pV[i]);
        lS += normal[i]*dV[i];
    }
    bool isComponentHit = false;
    double t = rS / lS;

    //Existiert ein sinnvoller Schnittpunkt oder annähernd parallel zwischen Ebene und Gerade?
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
        mHigh = (radiusH/2) * mHigh;
        mWidth = (radiusW/2) * mWidth;

        //Vektor von Mittelpunkt zum Intersect erstellen
        std::vector<double> intPos = intersect - position;

        //lS und rS wiederverwenden zur Speicheroptimierung
        rS = 0;
        lS = 0;

        //Überprüfen, ob in Grenze
        //Skalarprodukt aus Achse mit Intersect
        for (int i = 0; i < 3; i++) {
            rS += intPos[i] * mHigh[i];
            lS += intPos[i] * mWidth[i];
        }

        //lengthW und lengthH ist nicht deklariert
        double yProz = (rS / pow((radiusH/2), 2));
        double xProz = (lS / pow((radiusW/2), 2));
        xProz = xProz * (radiusW/2);
        yProz = yProz * (radiusH/2);

        double z = pow((xProz/radiusW), 2) + pow((yProz/radiusH), 2);

        if ((z<=1 && z>=-1) && calcOut(photon, intersect, normWidth)) {
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
bool MirrorElliptical::calcOut(Photon& p, std::vector<double>& intersect, std::vector<double>& normWidth) {
    //neuer Stützvektor wird der Schnittpunkt
    p.setPosition(intersect);

    std::vector<double> out(3);
    std::vector<double> dV = p.getDirection();
    double sumVE=0;
    double sumVN=0;

    //normierter Einfallsvektor berechnen
    for(int i=0; i<3; i++){
        sumVE += pow(dV[i], 2);
        sumVN += pow(normal[i], 2);
    }
    sumVE = sqrt(sumVE);
    sumVN = sqrt(sumVN);

    for(int i=0; i<3; i++){
        dV[i] /= sumVE;
        normal[i] /= sumVN;
    }

    //Skalarprodukt aus Einfallsvektor & einer Achse (normiert)
    double coalpha=0;
    for(int i=0; i<3; i++){
        coalpha += dV[i]*normal[i];
    }

    //Überprüfen ob der Winkel über 90 Grad
    if(coalpha>(M_PI_2)){
        coalpha = coalpha-(M_PI_2);
    }

    //In Formel einsetzen
    out = dV + (-2*(coalpha*(normal)));

    //An Photon übergeben
    p.setDirection(out);

    return true;
}

/**
 * @brief Standard get-method for getting the current radius(height) of the mirror
 * @return current radiusH of the mirror
 */
const double &MirrorElliptical::getRadiusH() {
    return radiusH;
}

/**
 * @brief Standard get-method for getting the current radius(width) of the mirror
 * @return current radiusW of the mirror
 */
const double &MirrorElliptical::getRadiusW() {
    return radiusW;
}

/**
 * @brief Standard set-method for setting a new radius(width) for the mirror
 * @param new radiusW for the mirror
 */
void MirrorElliptical::setRadiusW(double _radiusW) {
    radiusW = _radiusW;
}

/**
 * @brief Standard set-method for setting a new radius(height) for the mirror
 * @param new radiusH for the mirror
 */
void MirrorElliptical::setRadiusH(double _radiusH) {
    radiusH = _radiusH;
}

/**
 * @brief Constructs a mirrorElliptical
 * @param _position, sets the position of the new mirrorElliptical
 * @param _normal, sets the normal of the new mirrorElliptical
 * @param _radiusH, sets the radius(height) of the new mirrorElliptical
 * @param _radiusW, sets the radius(width) of the new mirrorElliptical
 * @param _type, sets the type of the component ("mirrorElliptical")
 */
MirrorElliptical::MirrorElliptical(std::vector<double>& _pos, std::vector<double>& _normal, double _radiusH, double _radiusW):Component(_pos, _normal, mirrorElliptical),radiusH(_radiusH),radiusW(_radiusW) {
}

/**
 * @brief Copys a mirrorElliptical
 * @param mirrorElliptical1, copy template for the new mirrorElliptical
 */
MirrorElliptical::MirrorElliptical(const MirrorElliptical &mirrorElliptical1): Component(mirrorElliptical1), radiusH(mirrorElliptical1.radiusH), radiusW(mirrorElliptical1.radiusW) {}
