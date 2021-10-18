#include "../include/importer.hpp"
#include <fstream>
#include "../../components/include/filter.hpp"
#include "../../components/include/lensOneSided.hpp"
#include "../../components/include/lensTwoSided.hpp"
#include "../../components/include/mirrorCircle.hpp"
#include "../../components/include/mirrorSquare.hpp"
#include "detector.hpp"

using namespace Config;

struct ImporterException : public std::exception {
    const char *what() const throw() {
        return "Error while import Setup";
    }
};

struct InvalidComponentException : public ImporterException {
    const char *what() const throw() {
        return "Invalid Component in Setup File";
    }
};

struct WrongTagException : public ImporterException {
    const char *what() const throw() {
        return "Wrong Parameter in Component";
    }
};

struct NotANumberException : public ImporterException {
    const char *what() const throw() {
        return "Not a valid Number";
    }
};


void Importer::importPosition(std::ifstream &_setupFile, std::vector<double> &_position) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, POSITION_OPENING_TAG);
        importVector(_setupFile, _position);
        getContentInBrackets(_setupFile, buf, POSITION_CLOSING_TAG);
        std::cout << "Position imported!" << std::endl;
    } catch (InvalidComponentException &e) {
        std::cerr << e.what() << std::endl << "Error occurred while creating Position Vector" << std::endl;
        throw InvalidComponentException();
    } catch (WrongTagException &e) {
        std::cerr << e.what() << std::endl << "Expected Parameter: " << POSITION_OPENING_TAG << std::endl
                  << "Retrieved Parameter: " << buf << std::endl;
        throw WrongTagException();
    }
}

void Importer::importNormal(std::ifstream &_setupFile, std::vector<double> &_normal) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, NORMAL_OPENING_TAG);
        importVector(_setupFile, _normal);
        getContentInBrackets(_setupFile, buf, NORMAL_CLOSING_TAG);
        std::cout << "Normal imported!" << std::endl;
    } catch (InvalidComponentException &e) {
        std::cerr << e.what() << std::endl << "Error occurred while creating Normal Vector" << std::endl;
        throw InvalidComponentException();
    } catch (WrongTagException &e) {
        std::cerr << e.what() << std::endl << "Expected Parameter: " << NORMAL_OPENING_TAG << std::endl
                  << "Retrieved Parameter: " << buf << std::endl;
        throw WrongTagException();
    }
}

void Importer::importPointOnEdge(std::ifstream &_setupFile, std::vector<double> &_pointOnEdge) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, POINT_ON_EDGE_OPENING_TAG);
        importVector(_setupFile, _pointOnEdge);
        getContentInBrackets(_setupFile, buf, POINT_ON_EDGE_CLOSING_TAG);
        std::cout << "PointOnEdge imported!" << std::endl;
    } catch (InvalidComponentException &e) {
        std::cerr << e.what() << std::endl << "Error occurred while creating PointOnEdge Vector" << std::endl;
        throw InvalidComponentException();
    } catch (WrongTagException &e) {
        std::cerr << e.what() << std::endl << "Expected Parameter: " << POINT_ON_EDGE_OPENING_TAG << std::endl
                  << "Retrieved Parameter: " << buf << std::endl;
        throw WrongTagException();
    }
}

void Importer::importPosOfPrevComponent(std::ifstream & _setupFile, std::vector<double> & _posOfPrev) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, POSITION_OF_PREVIOUS_COMPONENT_OPENING_TAG);
        importVector(_setupFile, _posOfPrev);
        getContentInBrackets(_setupFile, buf, POSITION_OF_PREVIOUS_COMPONENT_CLOSING_TAG);
        std::cout << "posOfPrevComponent imported!" << std::endl;
    } catch (InvalidComponentException &e) {
        std::cerr << e.what() << std::endl << "Error occurred while creating posOfPrevComponent Vector" << std::endl;
        throw InvalidComponentException();
    } catch (WrongTagException &e) {
        std::cerr << e.what() << std::endl << "Expected Parameter: " << POSITION_OF_PREVIOUS_COMPONENT_OPENING_TAG << std::endl
                  << "Retrieved Parameter: " << buf << std::endl;
        throw WrongTagException();
    }
}


void Importer::importVector(std::ifstream &_setupFile, std::vector<double> &_vector) {
    std::string buf;
    try {
        _setupFile >> buf;
        _vector[0] = std::stod(buf);
        _setupFile >> buf;
        _vector[1] = std::stod(buf);
        _setupFile >> buf;
        _vector[2] = std::stod(buf);
    } catch (std::exception &e) {
        std::cerr << std::endl << "Error while creation of a vector " << std::endl << "Current Buffer: " << buf
                  << std::endl << "Number was expected" << std::endl;
        throw InvalidComponentException();
    }
}

void Importer::importNumber(std::ifstream &_setupFile, const std::string &numberTag, int &importNumber) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, numberTag);
        _setupFile >> importNumber;
        getContentInBrackets(_setupFile, buf, "/" + numberTag);
        std::cout << numberTag << " imported!" << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Error while importing number" << std::endl << "Buffer: " + buf << std::endl;
        throw NotANumberException();
    }
}

void Importer::importNumber(std::ifstream &_setupFile, const std::string &numberTag, double &importNumber) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, numberTag);
        _setupFile >> importNumber;
        getContentInBrackets(_setupFile, buf, "/" + numberTag);
        std::cout << numberTag << " imported!" << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Error while importing number" << std::endl << "Buffer: " + buf << std::endl;
        throw NotANumberException();
    }
}

void Importer::importBool(std::ifstream &_setupFile, const std::string &boolTag, bool &importBool) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, boolTag);
        _setupFile >> importBool;
        getContentInBrackets(_setupFile, buf, "/" + boolTag);
        std::cout << boolTag << " imported!" << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Error while importing Bool" << std::endl << "Buffer: " + buf << std::endl;
        throw ImporterException();
    }
}

void Importer::getContentInBrackets(std::ifstream &file, std::string &buf, const std::string expectedString) {
    getContentInBrackets(file, buf);
    if (buf != expectedString) {
        throw WrongTagException();
    }
}

void Importer::getContentInBrackets(std::ifstream &file, std::string &buf) {
    std::getline(file, buf, '<');
    std::getline(file, buf, '>');
}

void Importer::importStp(List &_lst, std::string _filename) {
    std::ifstream setupFile;
    setupFile.open(_filename);
    std::string buf;
    getContentInBrackets(setupFile, buf, SETUP_OPENING_TAG);
    try {
        while (buf != SETUP_CLOSING_TAG && setupFile.is_open()) {
            getContentInBrackets(setupFile, buf);
            std::vector<double> _position(3);
            std::vector<double> _normal(3);
            if (buf == FILTER_OPENING_TAG) {
                int _lowerLim;
                int _upperLim;
                //Daten aus Datei einlesen
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, LOWER_LIMIT_OPENING_TAG, _lowerLim);
                importNumber(setupFile, UPPER_LIMIT_OPENING_TAG, _upperLim);
                _lst.append<Filter>(Filter(_position, _normal, _lowerLim, _upperLim));
                getContentInBrackets(setupFile, buf, FILTER_CLOSING_TAG);
                std::cout << "Filter imported!" << std::endl;
            } else if (buf == LENS_ONE_SIDED_OPENING_TAG) {
                double _refIndex;
                double _radiusH;
                double _radiusW;
                double _d;
                bool _planeIsFront;
                //Daten aus Datei einlesen
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, N_OPENING_TAG, _refIndex);
                importNumber(setupFile, RADIUS_H_OPENING_TAG, _radiusH);
                importNumber(setupFile, RADIUS_W_OPENING_TAG, _radiusW);
                importNumber(setupFile, D_OPENING_TAG, _d);
                importBool(setupFile, PLANE_IS_FRONT_OPENING_TAG, _planeIsFront);

                _lst.append<LensOneSided>(
                        LensOneSided(_position, _normal, _refIndex, _radiusH, _radiusW, _d, _planeIsFront));
                getContentInBrackets(setupFile, buf, LENS_ONE_SIDED_CLOSING_TAG);
                std::cout << LENS_ONE_SIDED_OPENING_TAG << " was imported!" << std::endl;
            } else if (buf == LENS_TWO_SIDED_OPENING_TAG) {
                double _refIndex;
                double _radiusH;
                double _radiusI;
                double _radiusO;
                double _d;
                //Daten aus Datei einlesen
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, N_OPENING_TAG, _refIndex);
                importNumber(setupFile, RADIUS_H_OPENING_TAG, _radiusH);
                importNumber(setupFile, RADIUS_I_OPENING_TAG, _radiusI);
                importNumber(setupFile, RADIUS_O_OPENING_TAG, _radiusO);
                importNumber(setupFile, D_OPENING_TAG, _d);

                _lst.append<LensTwoSided>(
                        LensTwoSided(_position, _normal, _refIndex, _radiusH, _radiusI, _radiusO, _d));
                getContentInBrackets(setupFile, buf, LENS_TWO_SIDED_CLOSING_TAG);
                std::cout << LENS_TWO_SIDED_OPENING_TAG << " was imported!" << std::endl;
            } else if (buf == MIRROR_ELLIPTICAL_OPENING_TAG) {
                double _radiusH;
                double _radiusW;
                //Daten aus Datei einlesen
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, RADIUS_H_OPENING_TAG, _radiusH);
                importNumber(setupFile, RADIUS_W_OPENING_TAG, _radiusW);

                _lst.append<MirrorElliptical>(MirrorElliptical(_position, _normal, _radiusH, _radiusW));
                getContentInBrackets(setupFile, buf, MIRROR_ELLIPTICAL_CLOSING_TAG);
                std::cout << MIRROR_ELLIPTICAL_OPENING_TAG << " was imported!" << std::endl;
            } else if (buf == MIRROR_CIRCLE_OPENING_TAG) {
                double _radius;
                //Daten aus Datei einlesen
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, RADIUS_OPENING_TAG, _radius);

                _lst.append<MirrorCircle>(MirrorCircle(_position, _normal, _radius));
                getContentInBrackets(setupFile, buf, MIRROR_CIRCLE_CLOSING_TAG);
                std::cout << MIRROR_CIRCLE_OPENING_TAG << " was imported!" << std::endl;
            } else if (buf == MIRROR_RECTANGLE_OPENING_TAG) {
                double _lengthH;
                double _lengthW;
                //Daten aus Datei einlesen
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, LENGTH_H_OPENING_TAG, _lengthH);
                importNumber(setupFile, LENGTH_W_OPENING_TAG, _lengthW);

                _lst.append<MirrorRectangle>(MirrorRectangle(_position, _normal, _lengthH, _lengthW));
                getContentInBrackets(setupFile, buf, MIRROR_RECTANGLE_CLOSING_TAG);
                std::cout << MIRROR_RECTANGLE_OPENING_TAG << " was imported!" << std::endl;
            } else if (buf == MIRROR_SQUARE_OPENING_TAG) {
                double _length;
                //Daten aus Datei einlesen
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, LENGTH_OPENING_TAG, _length);

                _lst.append<MirrorSquare>(MirrorSquare(_position, _normal, _length));
                getContentInBrackets(setupFile, buf, MIRROR_SQUARE_CLOSING_TAG);
                std::cout << MIRROR_SQUARE_OPENING_TAG << " was imported!" << std::endl;
            } else if(buf == DETECTOR_OPENING_TAG){
                std::vector<double> _pointOnEdge(3);
                std::vector<double> _posOfPreviousComponent(3);
                int size;
                double pixelSize;
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importPointOnEdge(setupFile, _pointOnEdge);
                importPosOfPrevComponent(setupFile, _posOfPreviousComponent);
                importNumber(setupFile, SIZE_OPENING_TAG,size);
                importNumber(setupFile, PIXEL_SIZE_OPENING_TAG, pixelSize);

                _lst.append<Detector>(Detector(_position, _normal, _pointOnEdge, _posOfPreviousComponent, size, pixelSize));
                getContentInBrackets(setupFile, buf, DETECTOR_CLOSING_TAG);
                std::cout << DETECTOR_OPENING_TAG << " was imported!" << std::endl;
            }else if (buf == SETUP_CLOSING_TAG) {
                break;
            } else {
                throw InvalidComponentException();
            }
        }
        std::cout << "Setup imported!" << std::endl;
    } catch (ImporterException e) {
        std::cerr << e.what() << std::endl;
    }
    setupFile.close();
}

void Importer::importObject(Config::object &_object, std::string filename) {
    std::ifstream setupFile;
    setupFile.open(filename);
    std::string buf;
    int i = 0;
    try {
        getContentInBrackets(setupFile, buf, OBJECT_OPENING_TAG);
        while (buf != OBJECT_CLOSING_TAG && setupFile.is_open()) {
            getContentInBrackets(setupFile, buf);
            Config::objectRow rowBuffer;
            while (buf != OBJECT_ROW_CLOSING_TAG && setupFile.is_open()) {
                std::vector<double> position(3);
                getContentInBrackets(setupFile, buf);
                if (buf == POINT_OPENING_TAG) {
                    importPosition(setupFile, position);
                    int wavelength;
                    importNumber(setupFile, WAVELENGTH_OPENING_TAG, wavelength);
                    objectPoint point(position, wavelength);
                    rowBuffer.push_back(point);
                    getContentInBrackets(setupFile, buf, POINT_CLOSING_TAG);
                    std::cout << ++i << std::endl;
                }
            }
            _object.push_back(rowBuffer);
            getContentInBrackets(setupFile, buf);
        }
    } catch (std::exception &e) {
        std::cerr << "Error while importing Object" << std::endl;
    }
}



