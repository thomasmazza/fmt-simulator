#include "../include/setupImporter.hpp"
#include <fstream>
#include "../../components/include/filter.hpp"
#include "../../components/include/lensOneSided.hpp"
#include "../../components/include/lensTwoSided.hpp"
#include "../../components/include/mirrorCircle.hpp"
#include "../../components/include/mirrorSquare.hpp"
struct ImporterException: public std::exception{
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

const std::string Importer::FILTER = "Filter";
const std::string Importer::LENS_ONE_SIDED = "LensOneSided";
const std::string Importer::LENS_TWO_SIDED = "LensTwoSided";
const std::string Importer::MIRROR_ELLIPTICAL = "MirrorElliptical";
const std::string Importer::MIRROR_CIRCLE = "MirrorCircle";
const std::string Importer::MIRROR_RECTANGLE = "MirrorRectangle";
const std::string Importer::MIRROR_SQUARE = "MirrorSquare";
const std::string Importer::SETUP_OPENING_TAG = "setup";
const std::string Importer::SETUP_CLOSING_TAG = "/setup";
const std::string Importer::POSITION_OPENING_TAG = "position";
const std::string Importer::POSITION_CLOSING_TAG = "/position";


void Importer::importPosition(std::ifstream &_setupFile, vector &_position) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, POSITION_OPENING_TAG);
        importVector(_setupFile, _position);
        getContentInBrackets(_setupFile, buf, POSITION_CLOSING_TAG);

    } catch (InvalidComponentException& e) {
        std::cerr <<e.what() << std::endl << "Error occurred while creating Position Vector" << std::endl;
        throw InvalidComponentException();
    } catch (WrongTagException& e){
        std::cerr << e.what() << std::endl <<"Expected Parameter: " << POSITION_OPENING_TAG << std::endl << "Retrieved Parameter: " << buf << std::endl;
        throw WrongTagException();
    }
}

void Importer::importNormal(std::ifstream &_setupFile, vector &_normal) {
    importVector(_setupFile, _normal);
    Utils::normalizeVector(_normal);
}

void Importer::importVector(std::ifstream &_setupFile, vector &_vector) {
    std::string buf;
    try {
        _setupFile >> buf;
        _vector[0] = std::stod(buf);
        _setupFile >> buf;
        _vector[1] = std::stod(buf);
        _setupFile >> buf;
        _vector[2] = std::stod(buf);
    } catch (std::exception &e) {
        std::cerr  << std::endl << "Error while creation of a vector " << std::endl << "Current Buffer: " << buf << std::endl << "Number was expected" << std::endl;
        throw InvalidComponentException();
    }
}

void Importer::getContentInBrackets(std::ifstream &file, std::string &buf, const std::string expectedString) {
    getContentInBrackets(file, buf);
    if (buf != expectedString){
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
    std::cout << setupFile.is_open() << std::endl;
    try {
        if (buf == SETUP_OPENING_TAG) {
            while (buf != SETUP_CLOSING_TAG && setupFile.is_open()) {
                try {
                    getContentInBrackets(setupFile, buf);
                    vector _position(3);
                    vector _normal(3);
                    if (buf == FILTER) {
                        int _lowerLim;
                        int _upperLim;
                        //Daten aus Datei einlesen
                        importPosition(setupFile, _position);
                        importNormal(setupFile, _normal);
                        setupFile >> buf;
                        _lowerLim = std::stoi(buf);
                        setupFile >> buf;
                        _upperLim = std::stoi(buf);
                        _lst.append<Filter>(Filter(_position, _normal, _lowerLim, _upperLim));
                    } else if (buf == LENS_ONE_SIDED) {
                        double _refIndex;
                        double _radiusH;
                        double _radiusW;
                        double _d;
                        bool _planeIsFront;
                        //Daten aus Datei einlesen
                        importPosition(setupFile, _position);
                        Utils::normalizeVector(_normal);
                        setupFile >> buf;
                        _refIndex = std::stod(buf);
                        setupFile >> buf;
                        _radiusH = std::stod(buf);
                        setupFile >> buf;
                        _radiusW = std::stod(buf);
                        setupFile >> buf;
                        _d = std::stod(buf);
                        setupFile >> buf;
                        _planeIsFront = std::stoi(buf);
                        _lst.append<LensOneSided>(
                                LensOneSided(_position, _normal, _refIndex, _radiusH, _radiusW, _d, _planeIsFront));
                    } else if (buf == LENS_TWO_SIDED) {
                        double _refIndex;
                        double _radiusH;
                        double _radiusI;
                        double _radiusO;
                        double _d;
                        //Daten aus Datei einlesen
                        importPosition(setupFile, _position);
                        Utils::normalizeVector(_normal);
                        setupFile >> buf;
                        _refIndex = std::stod(buf);
                        setupFile >> buf;
                        _radiusH = std::stod(buf);
                        setupFile >> buf;
                        _radiusI = std::stod(buf);
                        setupFile >> buf;
                        _radiusO = std::stod(buf);
                        setupFile >> buf;
                        _d = std::stod(buf);

                        _lst.append<LensTwoSided>(
                                LensTwoSided(_position, _normal, _refIndex, _radiusH, _radiusI, _radiusO, _d));
                    } else if (buf == MIRROR_ELLIPTICAL) {
                        double _rH;
                        double _rW;
                        //Daten aus Datei einlesen
                        importPosition(setupFile, _position);
                        Utils::normalizeVector(_normal);
                        setupFile >> buf;
                        _rH = std::stod(buf);
                        setupFile >> buf;
                        _rW = std::stod(buf);
                        _lst.append<MirrorElliptical>(MirrorElliptical(_position, _normal, _rH, _rW));
                    } else if (buf == MIRROR_CIRCLE) {
                        double _radius;
                        //Daten aus Datei einlesen
                        importPosition(setupFile, _position);
                        Utils::normalizeVector(_normal);
                        setupFile >> buf;
                        _radius = std::stod(buf);
                        _lst.append<MirrorCircle>(MirrorCircle(_position, _normal, _radius));
                    } else if (buf == MIRROR_RECTANGLE) {
                        double _lengthH;
                        double _lengthW;
                        //Daten aus Datei einlesen
                        importPosition(setupFile, _position);
                        Utils::normalizeVector(_normal);
                        setupFile >> buf;
                        _lengthH = std::stod(buf);
                        setupFile >> buf;
                        _lengthW = std::stod(buf);
                        _lst.append<MirrorRectangle>(MirrorRectangle(_position, _normal, _lengthH, _lengthW));
                    } else if (buf == MIRROR_SQUARE) {
                        double _length;
                        //Daten aus Datei einlesen
                        importPosition(setupFile, _position);
                        Utils::normalizeVector(_normal);
                        setupFile >> buf;
                        _length = std::stod(buf);
                        _lst.append<MirrorSquare>(MirrorSquare(_position, _normal, _length));
                    } else {
                        throw InvalidComponentException();
                    }
                } catch (ImporterException e) {
                    throw ImporterException();
                }
            }
        } else {
            std::cerr << "File " + _filename + " doesn't have Setup file Syntax" << std::endl;
        }
    } catch (ImporterException e) {
        std::cerr << e.what() << std::endl;
    }
}

Importer::Importer() {
}




