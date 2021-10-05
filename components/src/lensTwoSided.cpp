#include "lensTwoSided.hpp"
#include <boost/numeric/ublas/vector.hpp>


bool LensTwoSided::getOutDir(Photon& p){

    vector pV = p.getPosition();
    vector dV = p.getDirection();
    vector OM1(3);
    vector OM2(3);

    //Positionsvektor der MIttelpunkte der Kugeln bestimmen
    OM1 = position + radius1*normal;
    OM2 = position -normal*(d+radius2);

    //Summenvariablen für Schnittpunktberechnung erstellen
    double a=0;
    double b=0;
    double c=0;

    //Summenrechnung für quadratische Gleichung
    for(int i=0; i<3; i++){
        a += pow(dV[i], 2);
        b += 2*((pV[i]-OM1[i])*dV[i]);
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

    //Unterscheidung zwischen Sammellinse und Zerstreuungslinse und darauf folgend Schnittpunktberechnung
    if(radius1 > 0 && radius2 < 0){
        if(t1<t2){
            intersect = pV+t1*dV;
        }else{
            intersect = pV+t2*dV;
        }
    }else{
        if(t1>t2){
            intersect = pV+t1*dV;
        }else{
            intersect = pV+t2*dV;
        }
    }

    //Überprüfen ob im Höhenradius
    double d1 = (2*radius1 - sqrt( 4*pow(radius1, 2) - 4*pow(radiusH, 2) )) / 2;
    double sum1=0;
    vector check(3);
    check = intersect - (position - normal*d1);
    for(int i=0; i<3; i++){
        sum1 += pow(check[i], 2);
    }
    sum1 = sqrt(sum1);
    if(sum1>radiusH){
        return false;
    }

    //Flächennormale berechnen
    vector normalA1(3);
    if(radius1 > 0 && radius2 < 0){
        normalA1 = intersect - OM1;
    }else{
        normalA1 = OM1 - intersect;
    }

    //Normieren der Flächennormale und des Richtungsvektors + Skalarprodukt
    sum1=0;
    double sum2=0;
    double skpr1=0;
    for(int i=0; i<3; i++){
        sum1 += pow(normalA1[i], 2);
        sum2 += pow(dV[i], 2);
    }
    sum1 = sqrt(sum1);
    sum2 = sqrt(sum2);
    for(int i=0; i<3; i++){
        normalA1[i] = normalA1[i]/sum1;
        dV[i] = dV[i]/sum2;
        skpr1 += dV[i]*normalA1[i];
    }

    //Winkel berechnen
    vector coalphaV(3);
    double coalphaS=0;
    cross_product(coalphaV, dV, normalA1);
    for(int i=0; i<3; i++){
        coalphaS += pow(coalphaV[i], 2);
    }
    coalphaS = sqrt(coalphaS);

    if(coalphaS > 1.5){
        return false;
    }

    vector inLensDir(3);
    inLensDir = (1/n)*dV - normalA1*( (1/n)*(skpr1) - sqrt( 1 - pow((1/n), 2)* (1-pow(skpr1, 2)) ) );

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

    //Summenvariablen für Schnittpunktberechnung zurücksetzen
    a=0;
    b=0;
    c=0;

    for(int i=0; i<3; i++){
        a += pow(dV[i], 2);
        b += 2*((pV[i]-OM2[i])*dV[i]);
        c += pow((OM2[i]-pV[i]), 2) - pow(radius2, 2);
    }

    //Prüfen ob reele Lösung ex.
    if( (pow(b,2)-4*a*c) < 0 && a == 0){
        return false;
    }

    //Mögliche Lösungen als Variablen
    t1=0;
    t2=0;

    t1 = (-b+sqrt((pow(b,2)-4*a*c))) / (2*a);
    t2 = (-b-sqrt((pow(b,2)-4*a*c))) / (2*a);

    //Unterscheidung zwischen Sammellinse und Zerstreuungslinse und darauf folgend Schnittpunktberechnung
    if(radius1 > 0 && radius2 < 0){
        if(t1>t2){
            intersect = pV+t1*dV;
        }else{
            intersect = pV+t2*dV;
        }
    }else{
        if(t1<t2){
            intersect = pV+t1*dV;
        }else{
            intersect = pV+t2*dV;
        }
    }

    //Überprüfen ob im Höhenradius
    double d2 = (2*radius2 - sqrt( 4*pow(radius2, 2) - 4*pow(radiusH, 2) )) / 2;
    sum2=0;
    check = intersect - (position - normal*(d-d2));
    for(int i=0; i<3; i++){
        sum2 += pow(check[i], 2);
    }
    sum2 = sqrt(sum2);
    if(sum2>radiusH){
        return false;
    }

    //Flächennormale berechnen
    vector normalA2(3);
    if(radius1 > 0 && radius2 < 0){
        normalA2 = OM2 - intersect;
    }else{
        normalA2 = intersect - OM2;
    }

    //Normieren der Flächennormale und des Richtungsvektors + Skalarprodukt
    sum1=0;
    sum2=0;
    double skpr2=0;
    for(int i=0; i<3; i++){
        sum1 += pow(normalA2[i], 2);
        sum2 += pow(dV[i], 2);
    }
    sum1 = sqrt(sum1);
    sum2 = sqrt(sum2);
    for(int i=0; i<3; i++){
        normalA2[i] = normalA2[i]/sum1;
        dV[i] = dV[i]/sum2;
        skpr2 += dV[i]*normalA1[i];
    }

    //Winkel berechnen & überprüfen
    coalphaS=0;
    cross_product(coalphaV, dV, normalA1);
    for(int i=0; i<3; i++){
        coalphaS += pow(coalphaV[i], 2);
    }
    coalphaS = sqrt(coalphaS);

    if(coalphaS > 1.5){
        return false;
    }

    vector outLensDir(3);
    outLensDir = n*dV - normalA2*( n*(skpr2) - sqrt( 1 - pow(n, 2)* (1-pow(skpr2, 2)) ) );

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

    p.setPosition(pV);
    p.setDirection(dV);

    return true;
}

LensTwoSided::LensTwoSided(vector& _pos, vector& _normal,double _n, double _radiusH, double _radiusI, double _radiusO, double _d)
:LensTwoSided::Lens(_pos, _normal, _n, _radiusH, _d) {
    radius1 = _radiusI;
    radius2 = _radiusO;
}
