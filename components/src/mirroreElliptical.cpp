#include "mirrorElliptical.hpp"

bool MirrorElliptical::hitComponent(Photon& p, vector& _dirOA) {
    double rS=0;
    double lS=0;
    vector pV = p.getPos();
    vector dV = p.getDir();

    //Improvisierte Skalarprodukte
    for(int i=0; i<3; i++){
        rS += normal[i]*(position[i]-pV[i]);
        lS += normal[i]*dV[i];
    }

    //Existiert ein sinnvoller Schnittpunkt oder annähernd Parallel zw. Ebene und Gerade?
    if(!lS<0,000001){
        return false;
    }
    double t = rS/lS;
    vector intersect[3];

    //Berechne den Schnittpunkt
    for(int i=0; i<3; i++){
        intersect[i] = pV[i]+t*dV[i];
    }

    //Überprüfen ob im Bereich, Erst Bereich definieren
    vector mHigh[3];
    vector mWidth[3];
    mHigh = cross_product(_dirOA, normal);
    mWidth = cross_product(normal, mHigh);

    //Betrag berechnen
    rS = 0;  //lS und rS wiederverwenden zur Speicheroptimierung
    lS = 0;
    for(int i=0;  i<3; i++){
        lS = pow(mHigh[i], 2);
        rS = pow(mWidth[i], 2);
    }
    lS = sqrt(lS);
    rS = sqrt(rS);

    //normierte Vektoren berechnen
    for(int i=0;  i<3; i++){
        mHigh[i] = (mHigh[i]/lS);
        mWidth[i] = (mWidth[i]/rS);
    }
    vector normWidth = mWidth;

    //Vektor auf Höhe Skalieren
    mHigh = rH * mHigh;
    mWidth = rW * mWidth;

    //Vektor von Mittelpunkt zum Intersect erstellen
    intersect = intersect - pos;

    //lS und rS wiederverwenden zur Speicheroptimierung
    rS = 0;
    lS = 0;

    //Überprüfen ob in Grenze
    //Skalarprodukt aus Achse mit Intersect
    for(int i=0; i<3; i++){
        rS += intersect[i]*mHigh[i];
        lS += intersect[i]*mWidth[i];
    }
    double yProz = abs((rS/(pow(lengthH, 2))));
    double xProz = abs((lS/(pow(lengthW, 2))));
    xProz = xProz*lengthW;
    yProz = yProz*lengthH;

    double z = abs((pow(xProz,2)/lengthW)+(pow(yProz,2)/lengthH));

    if( z<=1 ){
        if (this.getOutDir(p, intersect, normWidth)){return true};
    }else{
        return false;
    }
}

void MirrorElliptical::getOutDir(Photon& p, vector& intersect, vector& normWidth) {
    //neuer Stützvektor wird der Schnittpunkt
    p.setPos(intersect);

    vector out[3];
    vector dV = p.getDir();
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
        dv[i] = (dV[i]/sumVE);
        normal[i] = (normal[i]/sumVN);
    }

    //Skalarprodukt aus Einfallsvektor & einer Achse (normiert)
    double coalpha=0;
    for(int i=0; i<3; i++){
        coalpha += dV[i]*normWidth[i];
    }

    //Überprüfen ob der Winkel über 90 Grad
    if(coalpha>(pi/2)){
        coalpha = coalpha-(pi/2);
    }

    //In Formel einsetzen
    out = dV +2*coalpha*(normal);

    //An Photon übergeben
    p.setDir(out);

    return true;
}

MirrorElliptical::MirrorElliptical(vector& pos, vector& _normal, double _rH, double _rW):Mirror(pos, _normal) {
    rH= _rH;
    rW= _rW;
}