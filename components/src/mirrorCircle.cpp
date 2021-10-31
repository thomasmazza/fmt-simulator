#include "../include/mirrorCircle.hpp"

#include "../../utils/include/utils.hpp"
#include <cmath>

/**
 * @brief Standard get-method for getting the current type of the component
 * @return type of the current component ("MirrorCircle")
 */
std::string MirrorCircle::getType() {
    return "MirrorCircle";
}

/**
 * @brief Main function of every component, calculates the position and direction after the photon passes
 * @param photon, Photon who should be calculated
 * @return true, if photon passes the mirror
 */
bool MirrorCircle::getOutDir(Photon& photon, std::vector<double>& _dirOA) {
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
        mHigh = (radius/2) * mHigh;
        mWidth = (radius/2) * mWidth;

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
        double yProz = (rS / pow((radius/2), 2));
        double xProz = (lS / pow((radius/2), 2));
        xProz = xProz * (radius/2);
        yProz = yProz * (radius/2);

        double z = pow((xProz/radius), 2) + pow((yProz/radius), 2);

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
bool MirrorCircle::calcOut(Photon& p, std::vector<double>& intersect, std::vector<double>& normWidth) {
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
 * @brief Standard set-method for setting a new radius for the mirror
 * @param new radius for the mirror
 */
void MirrorCircle::setRadius(double _radius) {
    radius = _radius;
}

/**
 * @brief Standard get-method for getting the current radius of the mirror
 * @return current radius of the lens
 */
double MirrorCircle::getRadius() {
    return radius;
}

/**
 * @brief Constructs a mirrorCircle
 * @param _position, sets the position of the new mirrorCircle
 * @param _normal, sets the normal of the new mirrorCircle
 * @param _radius, sets the radius of the new mirrorCircle
 * @param _type, sets the type of the component ("mirrorCircle")
 */
MirrorCircle::MirrorCircle(std::vector<double>& _pos, std::vector<double>& _normal, double _radius):Component(_pos,  _normal, mirrorCircle), radius(_radius){
}

/**
 * @brief Copys a mirrorCircle
 * @param mirrorCircle1, copy template for the new mirrorCircle
 */
MirrorCircle::MirrorCircle(const MirrorCircle &mirrorCircle1): Component(mirrorCircle1), radius(mirrorCircle1.radius) {}
