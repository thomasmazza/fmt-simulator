#include "../include/setupImporter.hpp"

#include "../../components/include/filter.hpp"
#include "../../components/include/lensOneSided.hpp"
#include "../../components/include/lensTwoSided.hpp"
#include "../../components/include/mirrorCircle.hpp"
#include "../../components/include/mirrorSquare.hpp"

namespace setup {
    const std::string Importer::FILTER = "Filter";
    const std::string Importer::LENS_ONE_SIDED =  "LensOneSided";
    const std::string Importer::LENS_TWO_SIDED =  "LensTwoSided";
    const std::string Importer::MIRROR_ELLIPTICAL =  "MirrorElliptical";
    const std::string Importer::MIRROR_CIRCLE =  "MirrorCircle";
    const std::string Importer::MIRROR_RECTANGLE =  "MirrorRectangle";
    const std::string Importer::MIRROR_SQUARE =  "MirrorSquare";


     void Importer::importPosNorm(std::ifstream& _dataIn, vector& _position, vector& _normal) {
        std::string buf;
        _dataIn >> buf; _position[0] = std::stod(buf);
        _dataIn >> buf; _position[1] = std::stod(buf);
        _dataIn >> buf; _position[2] = std::stod(buf);
        _dataIn >> buf; _normal[0] = std::stod(buf);
        _dataIn >> buf; _normal[1] = std::stod(buf);
        _dataIn >> buf; _normal[2] = std::stod(buf);
    }

     void Importer::normalizeVector(vector& _vec) {
        double vecAbs = 0;
        //Laenge des Vektors bestimmen
        for(int i = 0; i < 3; i++) vecAbs += pow(_vec[i], 2);
        vecAbs = sqrt(vecAbs);

        //Normierten Vektor berechnen
        for(int i = 0; i < 3; i++) _vec[i] = (_vec[i] / vecAbs);
    }

    void Importer::importStp(List& _lst, std::string _filename) {
        std::ifstream dataIn(_filename, std::ios::in);
        std::string buf;
        bool finish = false;

        while(!finish) {
            //Nach []-Brackets suchen und Inhalt speichern
            std::getline(dataIn, buf, '<');
            std::getline(dataIn, buf, '>');
            vector _position;
            vector _normal;
            if(buf==FILTER) {
                int _lowerLim;
                int _upperLim;
                //Daten aus Datei einlesen
                importPosNorm(dataIn, _position, _normal);
                normalizeVector(_normal);
                dataIn >> buf;
                _lowerLim = std::stoi(buf);
                dataIn >> buf;
                _upperLim = std::stoi(buf);
                _lst.append<Filter>(Filter(_position, _normal, _lowerLim, _upperLim));
            }else if(buf == LENS_ONE_SIDED){
                    double _refIndex;
                    double _radiusH;
                    double _radiusW;
                    double _d;
                    bool _planeIsFront;
                    //Daten aus Datei einlesen
                    importPosNorm(dataIn, _position, _normal);
                    normalizeVector(_normal);
                    dataIn >> buf;
                    _refIndex = std::stod(buf);
                    dataIn >> buf;
                    _radiusH = std::stod(buf);
                    dataIn >> buf; _radiusW = std::stod(buf);
                    dataIn >> buf; _d = std::stod(buf);
                    dataIn >> buf; _planeIsFront = std::stoi(buf);
                    _lst.append<LensOneSided>(LensOneSided(_position, _normal, _refIndex, _radiusH, _radiusW, _d, _planeIsFront));
        }else if(buf == LENS_TWO_SIDED) {
                double _refIndex;
                double _radiusH;
                double _radiusI;
                double _radiusO;
                double _d;
                //Daten aus Datei einlesen
                importPosNorm(dataIn, _position, _normal);
                normalizeVector(_normal);
                dataIn >> buf;
                _refIndex = std::stod(buf);
                dataIn >> buf;
                _radiusH = std::stod(buf);
                dataIn >> buf;
                _radiusI = std::stod(buf);
                dataIn >> buf;
                _radiusO = std::stod(buf);
                dataIn >> buf; _d = std::stod(buf);

                _lst.append<LensTwoSided>(LensTwoSided(_position, _normal, _refIndex, _radiusH, _radiusI, _radiusO, _d));
            }else if (buf == MIRROR_ELLIPTICAL){
                    double _rH; double _rW;
                    //Daten aus Datei einlesen
                    importPosNorm(dataIn, _position, _normal);
                    normalizeVector(_normal);
                    dataIn >> buf; _rH = std::stod(buf);
                    dataIn >> buf; _rW = std::stod(buf);
                                        _lst.append<MirrorElliptical>(MirrorElliptical(_position, _normal, _rH, _rW));
            }else if(buf == MIRROR_CIRCLE) {
                double _radius;
                //Daten aus Datei einlesen
                importPosNorm(dataIn, _position, _normal);
                normalizeVector(_normal);
                dataIn >> buf;
                _radius = std::stod(buf);
                _lst.append<MirrorCircle>(MirrorCircle(_position, _normal, _radius));
            }else if(buf == MIRROR_RECTANGLE) {
                double _lengthH;
                double _lengthW;
                //Daten aus Datei einlesen
                importPosNorm(dataIn, _position, _normal);
                normalizeVector(_normal);
                dataIn >> buf;
                _lengthH = std::stod(buf);
                dataIn >> buf;
                _lengthW = std::stod(buf);
                _lst.append<MirrorRectangle>(MirrorRectangle(_position, _normal, _lengthH, _lengthW));
            }else if(buf == MIRROR_SQUARE) {
                double _length;
                //Daten aus Datei einlesen
                importPosNorm(dataIn, _position, _normal);
                normalizeVector(_normal);
                dataIn >> buf;
                _length = std::stod(buf);
                _lst.append<MirrorSquare>(MirrorSquare(_position, _normal, _length));
            }else{
                    finish = true;
            }
        }
    }

    Importer::Importer() {
    }
}

