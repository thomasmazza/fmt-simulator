#include "../include/mirrorElliptical.hpp"

bool MirrorElliptical::hitComponent(Photon& photon, std::vector<double>& _dirOA) {
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
    if (abs(lS) > 0.000001 && t>0) {
        std::vector<double> intersect(3);

        //Berechne den Schnittpunkt
        for (int i = 0; i < 3; i++) {
            intersect[i] = pV[i] + t * dV[i];
        }

        //Überprüfen, ob im Bereich, erst Bereich definieren
        std::vector<double> mHigh(3);
        std::vector<double> mWidth(3);
        Utils::cross_product(mHigh, normal, _dirOA);
        Utils::cross_product(mWidth, mHigh, normal);

        //Betrag berechnen
        //lS und rS wiederverwenden zur Speicheroptimierung
        rS = 0;
        lS = 0;
        for (int i = 0; i < 3; i++) {
            lS += pow(mHigh[i], 2);
            rS += pow(mWidth[i], 2);
        }
        lS = sqrt(lS);
        rS = sqrt(rS);

        //normierte Vektoren berechnen
        for (int i = 0; i < 3; i++) {
            mHigh[i] = (mHigh[i] / lS);
            mWidth[i] = (mWidth[i] / rS);
        }
        std::vector<double> normWidth = mWidth;

        //Vektor auf Höhe Skalieren
        mHigh = radiusH * mHigh;
        mWidth = radiusW * mWidth;

        //Vektor von Mittelpunkt zum Intersect erstellen
        intersect = intersect - position;

        //lS und rS wiederverwenden zur Speicheroptimierung
        rS = 0;
        lS = 0;

        //Überprüfen, ob in Grenze
        //Skalarprodukt aus Achse mit Intersect
        for (int i = 0; i < 3; i++) {
            rS += intersect[i] * mHigh[i];
            lS += intersect[i] * mWidth[i];
        }

        //lengthW und lengthH ist nicht deklariert
        double yProz = abs((rS / pow(radiusH, 2)));
        double xProz = abs((lS / pow(radiusW, 2)));
        xProz = xProz * radiusW;
        yProz = yProz * radiusH;

        double z = abs(pow(xProz, 2) / radiusW + pow(yProz, 2) / radiusH);

        if (z <= 1 && getOutDir(photon, intersect, normWidth)) {
            isComponentHit = true;
        }
    }

    return isComponentHit;
}

bool MirrorElliptical::getOutDir(Photon& p, std::vector<double>& intersect, std::vector<double>& normWidth) {
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
        coalpha += dV[i]*normWidth[i];
    }

    //Überprüfen ob der Winkel über 90 Grad
    if(coalpha>(M_PI_2)){
        coalpha = coalpha-(M_PI_2);
    }

    //In Formel einsetzen
    out = dV +2*coalpha*(normal);

    //An Photon übergeben
    p.setDirection(out);

    return true;
}

const double &MirrorElliptical::getRadiusH() {
    return radiusH;
}

const double &MirrorElliptical::getRadiusW() {
    return radiusW;
}

MirrorElliptical::MirrorElliptical(std::vector<double>& _pos, std::vector<double>& _normal, double _radiusH, double _radiusW):Mirror(_pos, _normal, mirrorElliptical),radiusH(_radiusH),radiusW(_radiusW) {
}

MirrorElliptical::MirrorElliptical(std::vector<double> &_pos, std::vector<double> &_normal, double _radiusH, double _radiusW, ComponentType _type): Mirror(_pos, _normal, _type), radiusH(_radiusH), radiusW(_radiusW) {}
