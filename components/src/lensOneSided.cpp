#include "lensOneSided.hpp"
#include <boost/numeric/ublas/vector.hpp>


void LensOneSided::getOutDir(photon &p, vector &_dirOA) {
    if (planeIsFront) {
        double rS = 0;
        double lS = 0;
        vector pV = photon.getPosition();
        vector dV = photon.getDirection();

        //Improvisierte Skalarprodukte
        for (int i = 0; i < 3; i++) {
            rS += normal[i] * (position[i] - pV[i]);
            lS += normal[i] * dV[i];
        }

        //Existiert ein sinnvoller Schnittpunkt oder annähernd parallel zwischen Ebene und Gerade?
        if (lS < 0.000001) {

            double t = rS / lS;
            vector intersect(3);

            //Berechne den Schnittpunkt
            intersect = pV + t * dV;

            //Berechne Vektor von Pos bis zum Schnittpunkt
            vector posInter(3);
            posInter = intersect - position;
            t = 0;

            //Berechne Betrag von diesem Vektor
            for (int i = 0; i < 3; i++) {
                t += pow(posInter[i], 2);
            }
            t = sqrt(t);

            //Prüfe ob dieser Betrag kleiner als der Radius
            if (t > radiusH) {
                return false;
            }

            //Skalarprodukt

        }else{
            return false;
        }

    }else{

    }
}

LensOneSided::LensOneSided(vector& _pos, vector& _normal, double _refIndex, double _radiusH, double _radiusW, bool _planeIsFront)
:LensOneSided::Lens(_pos, _normal, _refIndex, _radiusH) {
    radiusW = _radiusW;
    planeIsFront = _planeIsFront;
}
