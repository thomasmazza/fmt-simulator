#include "../include/lensTwoSided.hpp"

#include "../../utils/include/utils.hpp"
#include <cmath>

/**
 * @brief Main function of every component, calculates the position and direction after the photon passes
 * @param photon, Photon who should be calculated
 * @return true, if photon passes the lens
 */
bool LensTwoSided::getOutDir(Photon& p){

    std::vector<double> pV = p.getPosition();
    std::vector<double> dV = p.getDirection();
    std::vector<double> OM1(3);
    std::vector<double> OM2(3);
    bool getsOut = false;

    //Positionsvektor der Mittelpunkte der Kugeln bestimmen
    OM1 = position - radiusI*normal;
    OM2 = position -normal*(d+radiusO);

    //Summenvariablen für Schnittpunktberechnung erstellen
    double a=0;
    double b=0;
    double c=0;

    //Summenrechnung für quadratische Gleichung
    for(int i=0; i<3; i++){
        a += pow(dV[i], 2);
        b += 2*((pV[i]-OM1[i])*dV[i]);
        c += pow((OM1[i]-pV[i]), 2);
    }
    c = c-pow(radiusI, 2);

    //Prüfen, ob reelle Lösung ex.
    if( (pow(b,2)-4*a*c) > 0) {

        //Mögliche Lösungen als Variablen
        double t1;
        double t2;

        t1 = (-b + sqrt((pow(b, 2) - 4 * a * c))) / (2 * a);
        t2 = (-b - sqrt((pow(b, 2) - 4 * a * c))) / (2 * a);
        std::vector<double> intersect(3);

        //Unterscheidung zwischen Sammellinse und Zerstreuungslinse und darauf folgend Schnittpunktberechnung

        if (radiusI > 0 && radiusO < 0) {
            if (t1 > 0 && t2 > 0) {
                if (t1 < t2) {
                    intersect = pV + t1 * dV;
                } else {
                    intersect = pV + t2 * dV;
                }
            } else if (t1 > 0) {
                intersect = pV + t1 * dV;
            } else if (t2 > 0) {
                intersect = pV + t2 * dV;
            } else {
                return false;
            }
        } else {
            if (t1 > 0 && t2 > 0) {
                if (t1 > t2) {
                    intersect = pV + t1 * dV;
                } else {
                    intersect = pV + t2 * dV;
                }
            } else if (t1 > 0) {
                intersect = pV + t1 * dV;
            } else if (t2 > 0) {
                intersect = pV + t2 * dV;
            } else {
                return false;
            }
        }

        //Überprüfen, ob im Höhenradius
        double d1 = abs(radiusI) - sqrt(pow(radiusI, 2) - pow(radiusH, 2));
        std::vector<double> check(3);
        if (radiusI > 0) {
            check = intersect - (position - normal * d1);
        } else {
            check = intersect - (position + normal * d1);
        }
        double sum1 = 0;
        for (int i = 0; i < 3; i++) {
            sum1 += pow(check[i], 2);
        }
        sum1 = sqrt(sum1);
        if (sum1 < radiusH) {

            //Flächennormale berechnen
            std::vector<double> normalA1(3);
            if (radiusI < 0 && radiusO > 0) {
                normalA1 = intersect - OM1;
            } else {
                normalA1 = OM1 - intersect;
            }

            //Normieren der Flächennormale und des Richtungsvektors + Skalarprodukt
            sum1 = 0;
            double sum2 = 0;
            double skpr1 = 0;
            for (int i = 0; i < 3; i++) {
                sum1 += pow(normalA1[i], 2);
                sum2 += pow(dV[i], 2);
            }
            sum1 = sqrt(sum1);
            sum2 = sqrt(sum2);
            for (int i = 0; i < 3; i++) {
                normalA1[i] = normalA1[i] / sum1;
                dV[i] = dV[i] / sum2;
                skpr1 += dV[i] * normalA1[i];
            }

            //Winkel berechnen
            std::vector<double> coalphaV(3);
            double coalphaS = 0;
            Utils::cross_product(coalphaV, dV, normalA1);
            for (int i = 0; i < 3; i++) {
                coalphaS += pow(coalphaV[i], 2);
            }
            coalphaS = sqrt(coalphaS);

            if (coalphaS < 1.4) {


                std::vector<double> inLensDir(3);
                inLensDir =
                        (1 / n) * dV - normalA1 * ((1 / n) * (skpr1) - sqrt(1 - pow((1 / n), 2) * (1 - pow(skpr1, 2))));

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
                //Summenvariablen für Schnittpunktberechnung zurücksetzen
                a = 0;
                b = 0;
                c = 0;

                for (int i = 0; i < 3; i++) {
                    a += pow(dV[i], 2);
                    b += 2 * ((pV[i] - OM2[i]) * dV[i]);
                    c += pow((OM2[i] - pV[i]), 2);
                }
                c = c - pow(radiusO, 2);

                //Prüfen, ob reelle Lösung ex.
                if ((pow(b, 2) - 4 * a * c) > 0) {

                    //Mögliche Lösungen als Variablen

                    t1 = (-b + sqrt((pow(b, 2) - 4 * a * c))) / (2 * a);
                    t2 = (-b - sqrt((pow(b, 2) - 4 * a * c))) / (2 * a);

                    //Unterscheidung zwischen Sammellinse und Zerstreuungslinse und darauf folgend Schnittpunktberechnung
                    if (radiusI > 0 && radiusO < 0) {
                        if (t1 > 0 && t2 > 0) {
                            if (t1 > t2) {
                                intersect = pV + t1 * dV;
                            } else {
                                intersect = pV + t2 * dV;
                            }
                        } else if (t1 > 0) {
                            intersect = pV + t1 * dV;
                        } else if (t2 > 0) {
                            intersect = pV + t2 * dV;
                        } else {
                            return false;
                        }
                    } else {
                        if (t1 > 0 && t2 > 0) {
                            if (t1 < t2) {
                                intersect = pV + t1 * dV;
                            } else {
                                intersect = pV + t2 * dV;
                            }
                        } else if (t1 > 0) {
                            intersect = pV + t1 * dV;
                        } else if (t2 > 0) {
                            intersect = pV + t2 * dV;
                        } else {
                            return false;
                        }
                    }

                    //Überprüfen, ob im Höhenradius
                    double d2 = abs(radiusO) - sqrt(pow(radiusO, 2) - pow(radiusH, 2));
                    sum2 = 0;
                    if (radiusO > 0) {
                        check = intersect - (position - (normal * (d2 + d)));
                    } else {
                        check = intersect - (position + (normal * (d2 - d)));
                    }
                    for (int i = 0; i < 3; i++) {
                        sum2 += pow(check[i], 2);
                    }
                    sum2 = sqrt(sum2);

                    if (sum2 < radiusH) {

                        //Flächennormale berechnen
                        std::vector<double> normalA2(3);
                        if (radiusI < 0 && radiusO > 0) {
                            normalA2 = OM2 - intersect;
                        } else {
                            normalA2 = intersect - OM2;
                        }

                        //Normieren der Flächennormale und des Richtungsvektors + Skalarprodukt
                        sum1 = 0;
                        sum2 = 0;
                        skpr1 = 0;
                        for (int i = 0; i < 3; i++) {
                            sum1 += pow(normalA2[i], 2);
                            sum2 += pow(dV[i], 2);
                        }
                        sum1 = sqrt(sum1);
                        sum2 = sqrt(sum2);
                        for (int i = 0; i < 3; i++) {
                            normalA2[i] = normalA2[i] / sum1;
                            dV[i] = dV[i] / sum2;
                            skpr1 += dV[i] * normalA1[i];
                        }

                        //Winkel berechnen & überprüfen
                        coalphaS = 0;
                        Utils::cross_product(coalphaV, dV, normalA1);
                        for (int i = 0; i < 3; i++) {
                            coalphaS += pow(coalphaV[i], 2);
                        }
                        coalphaS = sqrt(coalphaS);

                        if (coalphaS < 1.4) {

                            std::vector<double> outLensDir(3);
                            outLensDir = n * dV - normalA2 * (n * (skpr1) - sqrt(1 - pow(n, 2) * (1 - pow(skpr1, 2))));

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
                        }
                    }
                }
            }
        }
    }
    return getsOut;
}

/**
 * @brief Standard get-method for getting the current thickness of the lens
 * @return thickness of the lens
 */
const double &LensTwoSided::getD() {
    return d;
}

/**
 * @brief Standard get-method for getting the current refractive index of the material of the lens
 * @return refractive index of the material of the lens
 */
const double &LensTwoSided::getN(){
    return n;
}

/**
 * @brief Standard get-method for getting the current radius (height) of the lens
 * @return current radius (height) of the lens
 */
const double &LensTwoSided::getRadiusH() {
    return radiusH;
}

/**
 * @brief Standard set-method for setting a new refractive index of the material of the lens
 * @param new refractive index of the material of the lens
 */
void LensTwoSided::setN(double _n) {
    n = _n;
}

/**
 * @brief Standard set-method for setting a new thickness of the lens
 * @param new thickness of the lens
 */
void LensTwoSided::setD(double _d) {
    d = _d;
}

/**
 * @brief Standard set-method for setting a new radius (height) of the lens
 * @param new radius (height) of the lens
 */
void LensTwoSided::setRadiusH(double _radiusH) {
    radiusH = _radiusH;
}

/**
 * @brief Standard get-method for getting the current first radius (curvature) of the lens
 * @return current first radius (curvature) of the lens
 */
const double &LensTwoSided::getRadiusI() {
    return radiusI;
}

/**
 * @brief Standard get-method for getting the current second radius (curvature) of the lens
 * @return current second radius (curvature) of the lens
 */
const double &LensTwoSided::getRadiusO() {
    return radiusO;
}

/**
 * @brief Standard set-method for setting a new first radius (curvature) of the lens
 * @param new first radius (curvature) of the lens
 */
void LensTwoSided::setRadiusI(double _radiusI) {
    radiusI = _radiusI;
}

/**
 * @brief Standard set-method for setting a new second radius (curvature) of the lens
 * @param new second radius (curvature) of the lens
 */
void LensTwoSided::setRadiusO(double _radiusO) {
    radiusO = _radiusO;
}

/**
 * @brief Standard get-method for calculating the focal length of a lens
 * @return focal length of a lens
 */
const double &LensTwoSided::getF() {
    double r1 = abs(radiusI);
    double r2 = abs(radiusO);
    f = 1 / ((n - 1) * (1 / r1 + 1 / r2 - d * (n - 1) / (n * r1 * r2)));
    return f;
}

/**
 * @brief Constructs a lensTwoSided
 * @param _position, sets the position of the new lensTwoSided
 * @param _normal, sets the normal of the new lensTwoSided
 * @param _n, sets the ref. index of the new lensTwoSided
 * @param _d, sets the thickness of the new lensTwoSided
 * @param _radiusH, sets the radius(height) of the new lensTwoSided
 * @param _radiusI, sets the first radius(curvature) of the new lensTwoSided
 * @param _radiusO, sets the second radius(curvature) of the new lensTwoSided
 * @param _type, sets the type of the component ("lensTwoSided")
 */
LensTwoSided::LensTwoSided(std::vector<double>& _pos, std::vector<double>& _normal,double _n, double _radiusH, double _radiusI, double _radiusO, double _d)
:Component(_pos, _normal, lensTwoSided), n(_n), radiusH(_radiusH), radiusI(_radiusI), radiusO(_radiusO), d(_d) {
}

/**
 * @brief Copys a lensTwoSided
 * @param lensTwoSided1, copy template for the new lensTwoSided
 */
LensTwoSided::LensTwoSided(const LensTwoSided &lensTwoSided1):
    Component(lensTwoSided1), n(lensTwoSided1.n), radiusH(lensTwoSided1.radiusH), radiusI(lensTwoSided1.radiusI), radiusO(lensTwoSided1.radiusO), d(lensTwoSided1.d) {}
