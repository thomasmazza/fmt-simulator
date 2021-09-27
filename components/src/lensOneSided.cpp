#include "../include/lensOneSided.hpp"
#include <boost/numeric/ublas/vector.hpp>


void LensOneSided::getOutDir(photon &p, vector &_dirOA) {
    vector pV = photon.getPosition();
    vector dV = photon.getDirection();
    if (planeIsFront) {
        double rS = 0;
        double lS = 0;

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
            double skpr1=0;
            for(int i=0; i<3; i++){
                skrp1 = dV[i]*normal[i];
            }

            //Winkel berechnen
            vector coalphaV(3);
            double coalphaS=0;
            cross_product(coalphaV&, dV&, normalA&);
            for(int i=0; i<3; i++){
                coalphaS += pow(coalphaV[i], 2);
            }
            coalphaS = sqrt(coalphaS);

            if(coalphaS > 1.5){
                return false;
            }

            //Neuen Richtungsvektor berechnen
            vector inLensDir(3);
            inLensDir = (1/n)*dV - normal*( (1/n)*(skrp1) - sqrt( 1 - pow((1/n), 2)* (1-pow(skrp1, 2)) ) );

            //neue Richtung normieren
            t=0;
            for(int i=0; i<3; i++){
                t += pow(inLensDir[i], 2);
            }
            t=sqrt(t);
            for(int i=0; i<3; i++){
                inLensDir[i] = inLensDir[i]/t;
            }

            //neuer Ausgangspunkt und Richtung setzen
            dV = inLensDir;
            pV = intersect;

            //Schnittpunkt mit Kugel berechnen, zuerst Kugel formulieren
            vector OM1(3);
            OM1 = position - normal* (d-radiusW);

            //Summenvariablen für Schnittpunktberechnung erstellen
            double a=0;
            double b=0;
            double c=0;

            //Summenrechnung für quadratische Gleichung
            for(int i=0; i<3; i++){
                a += pow(dV[i], 2);
                b += 2*((pV[i]-OM1[i]*dV[i]);
                c += pow((OM1[i]-pV[i]), 2) - pow(radius1, 2);
            }

            //Prüfen ob reele Lösung ex.
            if( (pow(b,2)-4*a*c) < 0 && a == 0){
                return false;
            }

            //Mögliche Lösungen als Variablen
            double t1=0;
            double t2=0;

            t1 = (-b+sqrt((pow(b,2)-4*a*c))) / (2*a);
            t2 = (-b-sqrt((pow(b,2)-4*a*c))) / (2*a);

            //Unterscheidung zwischen Sammellinse und Zerstreuungslinse
            if(radiusW>0){
                if(t1<t2){
                    intersect = pV + t2*dV;
                }else{
                    intersect = pV + t1*dV;
                }
            }else{
                if(t1>t2){
                    intersect = pV + t2*dV;
                }else{
                    intersect = pV + t1*dV;
                }
            }

            //Überprüfen ob im Höhenradius
            double d1 = (2*radiusW - sqrt( 4*pow(radiusW, 2) - 4*pow(radiusH, 2) )) / 2;
            vector check = intersect - (position - normal*(d-d1));
            double sum1=0;
            for(int i=0; i<3; i++){
                sum1 += pow(check[i], 2);
            }
            sum1 = sqrt(sum1);
            if(sum1>radiusH){
                return false;
            }

            //Flächennormale berechnen
            vector normalA1(3);
            if(radiusW > 0){
                normalA1 = intersect - OM1;
            }else{
                normalA1 =  OM1 - intersect;
            }

            //Normieren der Flächennormale und des Richtungsvektors + Skalarprodukt
            sum1=0;
            skpr1=0;
            for(int i=0; i<3; i++) {
                sum1 += pow(normalA1[i], 2);
            }
            sum1 = sqrt(sum1);
            for(int i=0; i<3; i++) {
                normalA1[i] = normalA1[i] / sum1;
                skrp1 = dV[i]*normalA1[i];
            }

            //Winkel berechnen & überprüfen
            coalphaS=0;
            cross_product(coalphaV&, dV&, normalA1&);
            for(int i=0; i<3; i++){
                coalphaS += pow(coalphaV[i], 2);
            }
            coalphaS = sqrt(coalphaS);

            if(coalphaS > 1.5){
                return false;
            }

            vector outLensDir(3);
            outLensDir = n*dV - normalA1*( n*(skrp1) - sqrt( 1 - pow(n, 2)* (1-pow(skrp1, 2)) ) );

            //neuer Ausgangspunkt und Richtung normieren & setzen
            sum1=0;
            for(int i=0; i<3; i++){
                sum1 += pow(outLensDir[i], 2);
            }
            sum1=sqrt(sum1);
            for(int i=0; i<3; i++){
                outLensDir[i] = outLensDir[i]/sum1;
            }
            dV = outLensDir;
            pV = intersect;

            photon.setPos(pV);
            photon.setDir(dV);

            return true;
        }else{
            return false;
        }

    }else{
        //Schnittpunkt mit Kugel berechnen, zuerst Kugel formulieren
        vector OM1(3);
        OM1 = position - normal* (radiusW);

        //Summenvariablen für Schnittpunktberechnung erstellen
        double a=0;
        double b=0;
        double c=0;

        //Summenrechnung für quadratische Gleichung
        for(int i=0; i<3; i++){
            a += pow(dV[i], 2);
            b += 2*((pV[i]-OM1[i]*dV[i]);
            c += pow((OM1[i]-pV[i]), 2) - pow(radius1, 2);
        }

        //Prüfen ob reele Lösung ex.
        if( (pow(b,2)-4*a*c) < 0 && a == 0){
            return false;
        }

        //Mögliche Lösungen als Variablen
        double t1=0;
        double t2=0;

        t1 = (-b+sqrt((pow(b,2)-4*a*c))) / (2*a);
        t2 = (-b-sqrt((pow(b,2)-4*a*c))) / (2*a);
        vector intersect(3);

        //Unterscheidung zwischen Sammellinse und Zerstreuungslinse
        if(radiusW>0){
            if(t1<t2){
                intersect = pV + t1*dV;
            }else{
                intersect = pV + t2*dV;
            }
        }else{
            if(t1>t2){
                intersect = pV + t1*dV;
            }else{
                intersect = pV + t2dV;
            }
        }

        //Überprüfen ob im Höhenradius
        double d1 = (2*radiusW - sqrt( 4*pow(radiusW, 2) - 4*pow(radiusH, 2) )) / 2;
        vector check = intersect - (position - normal*(d1));
        double sum1=0;
        for(int i=0; i<3; i++){
            sum1 += pow(check[i], 2);
        }
        sum1 = sqrt(sum1);
        if(sum1>radiusH){
            return false;
        }

        //Flächennormale berechnen
        vector normalA1(3);
        if(radiusW > 0){
            normalA1 = intersect - OM1;
        }else{
            normalA1 =  OM1 - intersect;
        }

        //Normieren der Flächennormale und des Richtungsvektors + Skalarprodukt
        sum1=0;
        double skpr1=0;
        for(int i=0; i<3; i++) {
            sum1 += pow(normalA1[i], 2);
        }
        sum1 = sqrt(sum1);
        for(int i=0; i<3; i++) {
            normalA1[i] = normalA1[i] / sum1;
            skrp1 = dV[i]*normalA1[i];
        }

        //Winkel berechnen & überprüfen
        vector coalphaV(3);
        double coalphaS=0;
        cross_product(coalphaV&, dV&, normalA1&);
        for(int i=0; i<3; i++){
            coalphaS += pow(coalphaV[i], 2);
        }
        coalphaS = sqrt(coalphaS);

        if(coalphaS > 1.5){
            return false;
        }

        vector inLensDir(3);
        inLensDir = (1/n)*dV - normalA1*( (1/n)*(skrp1) - sqrt( 1 - pow((1/n), 2)* (1-pow(skrp1, 2)) ) );

        //neue Richtung normieren
        sum1=0;
        for(int i=0; i<3; i++){
            sum1 += pow(inLensDir[i], 2);
        }
        sum1=sqrt(sum1);
        for(int i=0; i<3; i++){
            inLensDir[i] = inLensDir[i]/sum1;
        }

        //neuer Ausgangspunkt und Richtung setzen
        dV = inLensDir;
        pV = intersect;

        //neue Normale der Planaren Fläche
        normalA1 = -normal;

        double rS = 0;
        double lS = 0;

        //Improvisierte Skalarprodukte
        for (int i = 0; i < 3; i++) {
            rS += normalA1[i] * (position[i] + d - pV[i]);
            lS += normalA1[i] * dV[i];
        }

        if (lS < 0.000001){
            double t = rS / lS;

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
            skpr1=0;
            for(int i=0; i<3; i++){
                skrp1 = dV[i]*(normalA1[i]);
            }

            //Winkel berechnen
            coalphaS=0;
            cross_product(coalphaV&, dV&, normalA1&);
            for(int i=0; i<3; i++){
                coalphaS += pow(coalphaV[i], 2);
            }
            coalphaS = sqrt(coalphaS);

            if(coalphaS > 1.5){
                return false;
            }

            //Neuen Richtungsvektor berechnen
            vector outLensDir(3);
            outLensDir = n*dV - normalA1*( n*(skrp1) - sqrt( 1 - pow(n, 2)* (1-pow(skrp1, 2)) ) );

            //neue Richtung normieren
            t=0;
            for(int i=0; i<3; i++){
                t += pow(outLensDir[i], 2);
            }
            t=sqrt(t);
            for(int i=0; i<3; i++){
                outLensDir[i] = outLensDir[i]/t;
            }

            //neuer Ausgangspunkt und Richtung setzen
            dV = outLensDir;
            pV = intersect;

            photon.setPos(pV);
            photon.setDir(dV);

            return true;
        }

    }
}

std::string LensOneSided::getType() {
    return "LensOneSided";
}

double LensOneSided::getRadiusW() {
    return radiusW;
}

bool LensOneSided::getPlaneIsFront() {
    return planeIsFront;
}

LensOneSided::LensOneSided(vector& _pos, vector& _normal, double _refIndex, double _radiusH, double _radiusW, bool _planeIsFront)
:LensOneSided::Lens(_pos, _normal, _refIndex, _radiusH) {
    radiusW = _radiusW;
    planeIsFront = _planeIsFront;
}
