#include "../include/setupImporter.hpp"

#include "../../components/include/filter.hpp"
#include "../../components/include/lensOneSided.hpp"
#include "../../components/include/lensTwoSided.hpp"
#include "../../components/include/mirrorCircle.hpp"
#include "../../components/include/mirrorSquare.hpp"

namespace setup {
    static void Importer::importPosNorm(std::ifstream& _dataIn, vector& _position, vector& _normal) {
        std::string buf;
        _dataIn >> buf; _position[0] = std::stod(buf);
        _dataIn >> buf; _position[1] = std::stod(buf);
        _dataIn >> buf; _position[2] = std::stod(buf);
        _dataIn >> buf; _normal[0] = std::stod(buf);
        _dataIn >> buf; _normal[1] = std::stod(buf);
        _dataIn >> buf; _normal[2] = std::stod(buf);
    }

    static void Importer::normalizeVector(vector& _vec) {
        double vecAbs = 0;
        //Laenge des Vektors bestimmen
        for(int i = 0; i < 3; i++) vecAbs += pow(_vec[i], 2);
        vecAbs = sqrt(vecAbs);

        //Normierten Vektor berechnen
        for(int i = 0; i < 3; i++) _vec[i] = (_vec[i] / vecAbs);
    }

    static void Importer::importStp(List& _lst, std::string _filename) {
        std::ifstream dataIn(_filename, std::ios::in);
        std::string buf;
        bool finish = false;

        while(!finish) {
            //Nach []-Brackets suchen und Inhalt speichern
            std::getline(dataIn, buf, '[');
            std::getline(dataIn, buf, ']');
            switch(buf) {
                case "Filter":
                    vector _position; vector _normal;
                    int _lowerLim; int _upperLim;
                    //Daten aus Datei einlesen
                    importPosNorm(dataIn, _position, _normal);
                    normalizeVector(_normal);
                    dataIn >> buf; _lowerLim = std::stoi(buf);
                    dataIn >> buf; _upperLim = std::stoi(buf);
                    _lst.append<Filter>(Filter::Filter(_position, _normal, _lowerLim, _upperLim));
                    break;
                case "LensOneSided":
                    vector _position; vector _normal;
                    double _refIndex; double _radiusH; double _radiusW; bool _planeIsFront;
                    //Daten aus Datei einlesen
                    importPosNorm(dataIn, _position, _normal);
                    normalizeVector(_normal);
                    dataIn >> buf; _refIndex = std::stod(buf);
                    dataIn >> buf; _radiusH = std::stod(buf);
                    dataIn >> buf; _radiusW = std::stod(buf);
                    dataIn >> buf; _planeIsFront = std::stoi(buf);
                    _lst.append<LensOneSided>(LensOneSided::LensOneSided(_position, _normal, _refIndex, _radiusH, _radiusW, _planeIsFront));
                    break;
                case "LensTwoSided":
                    vector _position; vector _normal;
                    double _refIndex; double _radiusH; double _radiusI; double _radiusO;
                    //Daten aus Datei einlesen
                    importPosNorm(data+In, _position, _normal);
                    normalizeVector(_normal);
                    dataIn >> buf; _refIndex = std::stod(buf);
                    dataIn >> buf; _radiusH = std::stod(buf);
                    dataIn >> buf; _radiusI = std::stod(buf);
                    dataIn >> buf; _radiusO = std::stod(buf);
                    _lst.append<LensTwoSided>(LensTwoSided::LensTwoSided(_position, _normal, _refIndex, _radiusH, _radiusI, _radiusO));
                    break;
                case "MirrorElliptical":
                    vector _position; vector _normal;
                    double _rH; double _rW;
                    //Daten aus Datei einlesen
                    importPosNorm(dataIn, _position, _normal);
                    normalizeVector(_normal);
                    dataIn >> buf; _rH = std::stod(buf);
                    dataIn >> buf; _rW = std::stod(buf);
                    _lst.append<MirrorElliptical>(MirrorElliptical::MirrorElliptical(_position, _normal, _rH, _rW));
                    break;
                case "MirrorCircle":
                    vector _position; vector _normal;
                    double _radius;
                    //Daten aus Datei einlesen
                    importPosNorm(dataIn, _position, _normal);
                    normalizeVector(_normal);
                    dataIn >> buf; _radius = std::stod(buf);
                    _lst.append<MirrorCircle>(MirrorCircle::MirrorCircle(_position, _normal, _radius));
                    break;
                case "MirrorRectangle":
                    vector _position; vector _normal;
                    double _lengthH; double _lengthW;
                    //Daten aus Datei einlesen
                    importPosNorm(dataIn, _position, _normal);
                    normalizeVector(_normal);
                    dataIn >> buf; _lengthH = std::stod(buf);
                    dataIn >> buf; _lengthW = std::stod(buf);
                    _lst.append<MirrorRectangle>(MirrorRectangle::MirrorRectangle(_position, _normal, _lengthH, _lengthW));
                    break;
                case "MirrorSquare":
                    vector _position; vector _normal;
                    double _length;
                    //Daten aus Datei einlesen
                    importPosNorm(dataIn, _position, _normal);
                    normalizeVector(_normal);
                    dataIn >> buf; _length = std::stod(buf);
                    _lst.append<MirrorSquare>(MirrorSquare::MirrorSquare(_position, _normal, _length));
                    break;
                default:
                    finish = true;
                    break;
            }
        }
    }

    Importer::Importer() {
        //TODO: Nothing
    }
}

