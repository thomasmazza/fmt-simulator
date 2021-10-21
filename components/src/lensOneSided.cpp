#include "../include/lensOneSided.hpp"

#include "../../utils/include/utils.hpp"
#include <cmath>

bool LensOneSided::getOutDir(Photon &p) {
    std::vector<double> pV = p.getPosition();
    std::vector<double> dV = p.getDirection();
    double d1 = radiusW - sqrt(pow(radiusW, 2) - pow(radiusH, 2));
    bool getsOut = false;
    std::vector<double> negNormal = (-1)*normal;

    if (planeIsFront) {
        double rS = 0;
        double lS = 0;

        //Improvisierte Skalarprodukte
        for (int i = 0; i < 3; i++) {
            rS += normal[i] * (position[i] - pV[i]);
            lS += normal[i] * dV[i];
        }

        double t = rS / lS;

        //Existiert ein sinnvoller Schnittpunkt oder annähernd parallel zwischen Ebene und Gerade?
        if (abs(lS) > 0.000001 && t > 0) {

            std::vector<double> intersect(3);

            //Berechne den Schnittpunkt
            intersect = pV + t * dV;

            //Berechne Vektor von Pos bis zum Schnittpunkt
            std::vector<double> posInter(3);
            posInter = intersect - position;
            t = 0;

            //Berechne Betrag von diesem Vektor
            for (int i = 0; i < 3; i++) {
                t += pow(posInter[i], 2);
            }
            t = sqrt(t);

            //Prüfe, ob dieser Betrag kleiner als der Radius
            if (t < radiusH) {


            //Skalarprodukt
            double skpr1 = 0;
            for (int i = 0; i < 3; i++) {
                skpr1 += dV[i] * negNormal[i];
                }

                //Winkel berechnen
                std::vector<double> coalphaV(3);
            double coalphaS = 0;
            Utils::cross_product(coalphaV, dV, normal);
            for (int i = 0; i < 3; i++) {
                coalphaS += pow(coalphaV[i], 2);
            }
            coalphaS = sqrt(coalphaS);

                if (coalphaS < 1.5) {

                    //Neuen Richtungsvektor berechnen
                    std::vector<double> inLensDir(3);
            inLensDir = (1 / n) * dV -
                        negNormal * ((1 / n) * (skpr1) - sqrt(1 - (pow((1 / n), 2) * (1 - pow(skpr1, 2)))));

                    //neue Richtung normieren
                    t = 0;
                    for (int i = 0; i < 3; i++) {
                        t += pow(inLensDir[i], 2);
                    }
                    t = sqrt(t);
                    for (int i = 0; i < 3; i++) {
                        inLensDir[i] = inLensDir[i] / t;
                    }

                    //neuer Ausgangspunkt und Richtung setzen
                    dV = inLensDir;
                    pV = intersect;
                    //Schnittpunkt mit Kugel berechnen, zuerst Kugel formulieren
                    std::vector<double> OM1(3);
            OM1 = position - normal * (d1 - radiusW);

            //Summenvariablen für Schnittpunktberechnung erstellen
            double a = 0;
            double b = 0;
            double c = 0;
            std::vector<double> P = pV - OM1;

            //Summenrechnung für quadratische Gleichung
            for (int i = 0; i < 3; i++) {
                a += pow(dV[i], 2);
                b += 2 * ((pV[i]-OM1[i] )* dV[i]);
                c += pow((pV[i]-OM1[i]), 2);
            }
            c = c - pow(radiusW, 2);

            //Prüfen ob reele Lösung ex.
            if ((pow(b, 2) - 4 * a * c) > 0) {

            //Mögliche Lösungen als Variablen
            double t1 ;
            double t2 ;

                        t1 = (-b + sqrt((pow(b, 2) - 4 * a * c))) / (2 * a);
                        t2 = (-b - sqrt((pow(b, 2) - 4 * a * c))) / (2 * a);

                        //Unterscheidung zwischen Sammellinse und Zerstreuungslinse
                        if (radiusW > 0) {
                            if (t1 < t2) {
                                intersect = pV + t2 * dV;
                            } else {
                                intersect = pV + t1 * dV;
                            }
                        } else {
                            if (t1 > t2) {
                                intersect = pV + t2 * dV;
                            } else {
                                intersect = pV + t1 * dV;
                            }
                        }

                        //Überprüfen ob im Höhenradius
                        std::vector<double> check = intersect - position;
            double sum1 = 0;
            for (int i = 0; i < 3; i++) {
                sum1 += pow(check[i], 2);
            }
            sum1 = sqrt(sum1);
            if (sum1 < radiusH) {


                            //Flächennormale berechnen
                            std::vector<double> normalA1(3);
            if (radiusW > 0) {
                normalA1 = intersect - OM1;
            } else {
                normalA1 = OM1 - intersect;
            }

                            //Normieren der Flächennormale und des Richtungsvektors + Skalarprodukt
                            sum1 = 0;
                            skpr1 = 0;
                            for (int i = 0; i < 3; i++) {
                                sum1 += pow(normalA1[i], 2);
                            }
                            sum1 = sqrt(sum1);
                            for (int i = 0; i < 3; i++) {
                                normalA1[i] = normalA1[i] / sum1;
                                skpr1 += dV[i] * normalA1[i];
                            }

                            //Winkel berechnen & überprüfen
                            coalphaS = 0;
                            Utils::cross_product(coalphaV, dV, normalA1);
                            for (int i = 0; i < 3; i++) {
                                coalphaS += pow(coalphaV[i], 2);
                            }
                            coalphaS = sqrt(coalphaS);

                            if (coalphaS < 1.5) {

                                std::vector<double> outLensDir(3);
            outLensDir = n * dV - normalA1 * (n * (skpr1) - sqrt(1 - pow(n, 2) * (1 - pow(skpr1, 2))));

                                //neuer Ausgangspunkt und Richtung normieren & setzen
                                sum1 = 0;
                                for (int i = 0; i < 3; i++) {
                                    sum1 += pow(outLensDir[i], 2);
                                }
                                sum1 = sqrt(sum1);
                                for (int i = 0; i < 3; i++) {
                                    outLensDir[i] = outLensDir[i] / sum1;
                                }
                                dV = outLensDir;
                                pV = intersect;

                                p.setPosition(pV);
                                p.setDirection(dV);

            getsOut = true;
        } }
                    }
                }
            }
        }else {
            getsOut = false;
        }

    } else {


        //Schnittpunkt mit Kugel berechnen, zuerst Kugel formulieren
        std::vector<double> OM1(3);
        OM1 = position - normal * (radiusW);

        //Summenvariablen für Schnittpunktberechnung erstellen
        double a = 0;
        double b = 0;
        double c = 0;

        //Summenrechnung für quadratische Gleichung
        for (int i = 0; i < 3; i++) {
            a += pow(dV[i], 2);
            b += 2 * ((pV[i] - OM1[i]) * dV[i]);
            c += pow((pV[i] - OM1[i]), 2);
        }
        c = c - pow(radiusW, 2);

        //Prüfen ob reele Lösung ex.
        if ((pow(b, 2) - 4 * a * c) > 0) {

        //Mögliche Lösungen als Variablen
        double t1 ;
        double t2 ;

        t1 = (-b + sqrt((pow(b, 2) - 4 * a * c))) / (2 * a);
        t2 = (-b - sqrt((pow(b, 2) - 4 * a * c))) / (2 * a);
        std::vector<double> intersect(3);

            //Unterscheidung zwischen Sammellinse und Zerstreuungslinse
            if (radiusW > 0) {
                if (t1 < t2) {
                    intersect = pV + t1 * dV;
                } else {
                    intersect = pV + t2 * dV;
                }
            } else {
                if (t1 > t2) {
                    intersect = pV + t1 * dV;
                } else {
                    intersect = pV + t2 * dV;
                }
            }

            //Überprüfen ob im Höhenradius
            std::vector<double> check = intersect - position;
        double sum1 = 0;
        for (int i = 0; i < 3; i++) {
            sum1 += pow(check[i], 2);
        }
        sum1 = sqrt(sum1);
        if (sum1 < radiusH) {


                //Flächennormale berechnen
                std::vector<double> normalA1(3);
        if (radiusW < 0) {
            normalA1 = intersect - OM1;
        } else {
            normalA1 = OM1 - intersect;
        }

                //Normieren der Flächennormale und des Richtungsvektors + Skalarprodukt
                sum1 = 0;
                double skpr1 = 0;
                for (int i = 0; i < 3; i++) {
                    sum1 += pow(normalA1[i], 2);
                }
                sum1 = sqrt(sum1);
                for (int i = 0; i < 3; i++) {
                    normalA1[i] = normalA1[i] / sum1;
                    skpr1 += dV[i] * normalA1[i];
                }

                //Winkel berechnen & überprüfen
                std::vector<double> coalphaV(3);
        double coalphaS = 0;
        Utils::cross_product(coalphaV, dV, normalA1);
        for (int i = 0; i < 3; i++) {
            coalphaS += pow(coalphaV[i], 2);
        }
        coalphaS = sqrt(coalphaS);

                if (coalphaS < 1.5) {

                    std::vector<double> inLensDir(3);
        inLensDir = (1 / n) * dV - normalA1 * ((1 / n) * (skpr1) - sqrt(1 - pow((1 / n), 2) * (1 - pow(skpr1, 2))));

                    //neue Richtung normieren
                    sum1 = 0;
                    for (int i = 0; i < 3; i++) {
                        sum1 += pow(inLensDir[i], 2);
                    }
                    sum1 = sqrt(sum1);
                    for (int i = 0; i < 3; i++) {
                        inLensDir[i] = inLensDir[i] / sum1;
                    }

                    //neuer Ausgangspunkt und Richtung setzen
                    dV = inLensDir;
                    pV = intersect;

                    //neue Normale der Planaren Fläche
                    normalA1 = normal*(-1);

                    double rS = 0;
                    double lS = 0;

                    //Improvisierte Skalarprodukte
                    for (int i = 0; i < 3; i++) {
                        rS += normalA1[i] * (position[i] + d1 - pV[i]);
                        lS += normalA1[i] * dV[i];
                    }
                    double t = rS / lS;

                    if (abs(lS) > 0.000001 && t > 0) {

                        //Berechne den Schnittpunkt
                        intersect = pV + t * dV;

                        //Berechne Vektor von Pos bis zum Schnittpunkt
                        std::vector<double> posInter(3);
                        posInter = intersect - position;


                        //Berechne Betrag von diesem Vektor
                        t = 0;
                        for (int i = 0; i < 3; i++) {
                            t += pow(posInter[i], 2);
                        }
                        t = sqrt(t);

                        //Prüfe, ob dieser Betrag kleiner als der Radius
                        if (t < radiusH) {

                            //Skalarprodukt
                            skpr1 = 0;
                            for (int i = 0; i < 3; i++) {
                                skpr1 += dV[i] * (normalA1[i]);
                            }

                            //Winkel berechnen
                            coalphaS = 0;
                            Utils::cross_product(coalphaV, dV, normalA1);
                            for (int i = 0; i < 3; i++) {
                                coalphaS += pow(coalphaV[i], 2);
                            }
                            coalphaS = sqrt(coalphaS);

                            if (coalphaS < 1.5) {

                                //Neuen Richtungsvektor berechnen
                                std::vector<double> outLensDir(3);
            outLensDir = n * dV - normalA1 * (n * (skpr1) - sqrt(1 - pow(n, 2) * (1 - pow(skpr1, 2))));

                                //neue Richtung normieren
                                t = 0;
                                for (int i = 0; i < 3; i++) {
                                    t += pow(outLensDir[i], 2);
                                }
                                t = sqrt(t);
                                for (int i = 0; i < 3; i++) {
                                    outLensDir[i] = outLensDir[i] / t;
                                }

                                //neuer Ausgangspunkt und Richtung setzen
                                dV = outLensDir;
                                pV = intersect;

                                p.setPosition(pV);
                                p.setDirection(dV);

                                getsOut = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return getsOut;
}

const double &LensOneSided::getD() {
    return d;
}

const double &LensOneSided::getN(){
    return n;
}

const double &LensOneSided::getRadiusH() {
    return radiusH;
}

void LensOneSided::setN(double _n) {
    n = _n;
}

void LensOneSided::setD(double _d) {
    d = _d;
}

void LensOneSided::setRadiusH(double _radiusH) {
    radiusH = _radiusH;
}

const double &LensOneSided::getRadiusW() {
    return radiusW;
}

const bool &LensOneSided::getPlaneIsFront() {
    return planeIsFront;
}

void LensOneSided::setPlaneIsFront(bool _planeIsFront) {
    planeIsFront =_planeIsFront;
}

void LensOneSided::setRadiusW(double _radiusW) {
    radiusW = _radiusW;
}

LensOneSided::LensOneSided(std::vector<double> &_pos, std::vector<double> &_normal, double _n, double _radiusH, double _radiusW, double _d,
                           bool _planeIsFront) : Component(_pos, _normal, lensOneSided), n(_n), radiusH(_radiusH), radiusW(_radiusW), d(_d), planeIsFront(_planeIsFront) {
}

LensOneSided::LensOneSided(const LensOneSided &lensOneSided1):
    Component(lensOneSided1), n(lensOneSided1.n), radiusH(lensOneSided1.radiusH), radiusW(lensOneSided1.radiusW), d(lensOneSided1.d), planeIsFront(lensOneSided1.planeIsFront) {}
