#include "ellipticalMirror.hpp"

bool EllipticalMirror::hitComponent(Photon& p, vector& _dirOA) {
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
        if (this.getOutDir(p, intersect)){return true};
    }else{
        return false;
    }
}

void EllipticalMirror::getOutDir(Photon& p) {
    //TODO: Logik einbauen
}

EllipticalMirror::EllipticalMirror(vector& pos, vector& _normal, double _rH, double _rW):Mirror(pos, _normal) {
    rH= _rH;
    rW= _rW;
}