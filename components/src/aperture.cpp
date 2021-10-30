#include "../include/aperture.hpp"

#include "../../utils/include/utils.hpp"
#include <cmath>

std::string Aperture::getType() {
    return "Aperture";
}

bool Aperture::getOutDir(Photon& photon, std::vector<double>& _dirOA) {
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

        if ((z<=1 && z>=-1)) {
            isComponentHit = true;
        }
    }

    return isComponentHit;
}


void Aperture::setRadius(double _radius) {
    radius = _radius;
}

double Aperture::getRadius() {
    return radius;
}
Aperture::Aperture(std::vector<double>& _pos, std::vector<double>& _normal, double _radius):Component(_pos,  _normal, aperture), radius(_radius){
}

Aperture::Aperture(const Aperture &aperture1): Component(aperture1), radius(aperture1.radius) {}
