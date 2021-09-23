#include "mirrorElliptical.hpp"

bool MirrorElliptical::hitComponent(Photon& photon, vector& _dirOA) {
    double rS=0;
    double lS=0;
    vector pV = photon.getPosition();
    vector dV = photon.getDirection();

    //Improvisierte Skalarprodukte
    for(int i=0; i<3; i++){
        rS += normal(i)*(position(i)-pV(i));
        lS += normal(i)*dV(i);
    }

    //Existiert ein sinnvoller Schnittpunkt oder annähernd parallel zwischen Ebene und Gerade?
    if (lS < 0.000001) {
        double t = rS / lS;
        vector intersect(3);

        //Berechne den Schnittpunkt
        for (int i = 0; i < 3; i++) {
            intersect(i) = pV(i) + t * dV(i);
        }

        //Überprüfen, ob im Bereich, erst Bereich definieren
        vector mHigh(3);
        vector mWidth(3);
        mHigh = boost::geometry::cross_product(_dirOA, normal);
        mWidth = boost::geometry::cross_product(normal, mHigh);

        //Betrag berechnen
        //lS und rS wiederverwenden zur Speicheroptimierung
        rS = 0;
        lS = 0;
        for (int i = 0; i < 3; i++) {
            lS = pow(mHigh[i], 2);
            rS = pow(mWidth[i], 2);
        }
        lS = sqrt(lS);
        rS = sqrt(rS);

        //normierte Vektoren berechnen
        for (int i = 0; i < 3; i++) {
            mHigh(i) = (mHigh(i) / lS);
            mWidth(i) = (mWidth(i) / rS);
        }
        vector normWidth = mWidth;

        //Vektor auf Höhe Skalieren
        mHigh = rH * mHigh;
        mWidth = rW * mWidth;

        //Vektor von Mittelpunkt zum Intersect erstellen
        intersect = intersect - position;

        //lS und rS wiederverwenden zur Speicheroptimierung
        rS = 0;
        lS = 0;

        //Überprüfen, ob in Grenze
        //Skalarprodukt aus Achse mit Intersect
        for (int i = 0; i < 3; i++) {
            rS += intersect(i) * mHigh(i);
            lS += intersect(i) * mWidth(i);
        }

        //lengthW und lengthH ist nicht deklariert
        double yProz = abs((rS / pow(lengthH, 2)));
        double xProz = abs((lS / pow(lengthW, 2)));
        xProz = xProz * lengthW;
        yProz = yProz * lengthH;

        double z = abs(pow(xProz, 2) / lengthW + pow(yProz, 2) / lengthH);

        if (z <= 1 && getOutDir(photon, intersect, normWidth)) {
            return true;
        }
        return false;
    } else {
        return false;
    }
}

bool MirrorElliptical::getOutDir(Photon& p, vector& intersect, vector& normWidth) {
    //neuer Stützvektor wird der Schnittpunkt
    p.setPosition(intersect);

    vector out(3);
    vector dV = p.getDirection();
    double sumVE=0;
    double sumVN=0;

    //normierter Einfallsvektor berechnen
    for(int i=0; i<3; i++){
        sumVE += pow(dV(i), 2);
        sumVN += pow(normal(i), 2);
    }
    sumVE = sqrt(sumVE);
    sumVN = sqrt(sumVN);
    for(int i=0; i<3; i++){
        dV(i) = (dV(i)/sumVE);
        normal[i] = (normal[i]/sumVN);
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

MirrorElliptical::MirrorElliptical(vector& pos, vector& _normal, double _rH, double _rW):Mirror(pos, _normal) {
    rH= _rH;
    rW= _rW;
}