#include "../include/mirrorSquare.hpp"

#include "../../utils/include/utils.hpp"
#include <cmath>

std::string MirrorSquare::getType() {
    return "MirrorSquare";
}

const double &MirrorSquare::getLength() {
    return length;
}

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

void MirrorSquare::setLength(double _length) {
    length = _length;
}

MirrorSquare::MirrorSquare(std::vector<double>& _pos, std::vector<double>& _normal, double _length):Component(_pos, _normal, mirrorSquare), length(_length){
}

MirrorSquare::MirrorSquare(const MirrorSquare &mirrorSquare1): Component(mirrorSquare1), length(mirrorSquare1.length) {}
