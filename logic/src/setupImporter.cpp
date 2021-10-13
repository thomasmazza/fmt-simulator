#include "../include/setupImporter.hpp"
#include <fstream>
#include "../../components/include/filter.hpp"
#include "../../components/include/lensOneSided.hpp"
#include "../../components/include/lensTwoSided.hpp"
#include "../../components/include/mirrorCircle.hpp"
#include "../../components/include/mirrorSquare.hpp"

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
    const char *what() const throw(){
        return "Not a valid Number";
    }
};

const std::string Importer::FILTER_OPENING_TAG = "Filter";
const std::string Importer::FILTER_CLOSING_TAG = "/Filter";
const std::string Importer::LENS_ONE_SIDED = "LensOneSided";
const std::string Importer::LENS_TWO_SIDED = "LensTwoSided";
const std::string Importer::MIRROR_ELLIPTICAL = "MirrorElliptical";
const std::string Importer::MIRROR_CIRCLE = "MirrorCircle";
const std::string Importer::MIRROR_RECTANGLE = "MirrorRectangle";
const std::string Importer::MIRROR_SQUARE = "MirrorSquare";
const std::string Importer::SETUP_OPENING_TAG = "Setup";
const std::string Importer::SETUP_CLOSING_TAG = "/Setup";
const std::string Importer::POSITION_OPENING_TAG = "Position";
const std::string Importer::POSITION_CLOSING_TAG = "/Position";
const std::string Importer::NORMAL_OPENING_TAG = "Normal";
const std::string Importer::NORMAL_CLOSING_TAG = "/Normal";
const std::string Importer::LOWER_LIMIT_OPENING_TAG = "LowerLimit";
const std::string Importer::LOWER_LIMIT_CLOSING_TAG = "/LowerLimit";
const std::string Importer::UPPER_LIMIT_OPENING_TAG = "UpperLimit";
const std::string Importer::UPPER_LIMIT_CLOSING_TAG = "/UpperLimit";
const std::string Importer::REF_INDEX_OPENING_TAG = "RefIndex";
const std::string Importer::REF_INDEX_CLOSING_TAG = "/RefIndex";
const std::string Importer::RADIUS_H_OPENING_TAG = "RadiusH";
const std::string Importer::RADIUS_H_CLOSING_TAG = "/RadiusH";
const std::string Importer::RADIUS_W_OPENING_TAG = "RadiusW";
const std::string Importer::RADIUS_W_CLOSING_TAG = "/RadiusW";
const std::string Importer::D_OPENING_TAG = "D";
const std::string Importer::D_CLOSING_TAG = "/D";


void Importer::importPosition(std::ifstream &_setupFile, vector &_position) {
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

void Importer::importNormal(std::ifstream &_setupFile, vector &_normal) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, NORMAL_OPENING_TAG);
        importVector(_setupFile, _normal);
        getContentInBrackets(_setupFile, buf, NORMAL_CLOSING_TAG);
        std::cout << "Normal imported!" << std::endl;
    } catch (InvalidComponentException &e) {
        std::cerr << e.what() << std::endl << "Error occurred while creating Position Vector" << std::endl;
        throw InvalidComponentException();
    } catch (WrongTagException &e) {
        std::cerr << e.what() << std::endl << "Expected Parameter: " << NORMAL_OPENING_TAG<< std::endl
                  << "Retrieved Parameter: " << buf << std::endl;
        throw WrongTagException();
    }
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
        std::cerr << std::endl << "Error while creation of a vector " << std::endl << "Current Buffer: " << buf
                  << std::endl << "Number was expected" << std::endl;
        throw InvalidComponentException();
    }
}

double Importer::importNumber(std::ifstream& _setupFile, const std::string& numberTag, int& importNumber ) {
    std::string buf;
    std::string number;
    try{
        getContentInBrackets(_setupFile, buf, numberTag);
        _setupFile >> number;
        getContentInBrackets(_setupFile, buf, "/"+numberTag);
        std::cout << numberTag << " imported!" << std::endl;
        return std::stoi(number);
    }catch (std::exception& e){
        std::cerr <<"Error while importing number" <<std::endl<<"Buffer: " + buf << std::endl;
        throw NotANumberException();
    }
}
double Importer::importNumber(std::ifstream& _setupFile, const std::string& numberTag, double& importNumber ) {
    std::string buf;
    std::string number;
    try{
        getContentInBrackets(_setupFile, buf, numberTag);
        _setupFile >> number;
        getContentInBrackets(_setupFile, buf, "/"+numberTag);
        std::cout << numberTag << " imported!" << std::endl;
        return std::stod(number);
    }catch (std::exception& e){
        std::cerr <<"Error while importing number" <<std::endl<<"Buffer: " + buf << std::endl;
        throw NotANumberException();
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
    std::cout << setupFile.is_open() << std::endl;
    try {
        if (buf == SETUP_OPENING_TAG) {
            while (buf != SETUP_CLOSING_TAG && setupFile.is_open()) {
                try {
                    getContentInBrackets(setupFile, buf);
                    vector _position(3);
                    vector _normal(3);
                    if (buf == FILTER_OPENING_TAG) {
                        int _lowerLim;
                        int _upperLim;
                        //Daten aus Datei einlesen
                        importPosition(setupFile, _position);
                        importNormal(setupFile, _normal);
                        importNumber(setupFile,LOWER_LIMIT_OPENING_TAG, _lowerLim);
                        importNumber(setupFile, UPPER_LIMIT_OPENING_TAG, _upperLim);
                        _lst.append<Filter>(Filter(_position, _normal, _lowerLim, _upperLim));
                        getContentInBrackets(setupFile, buf, FILTER_CLOSING_TAG);
                        std::cout << "Filter imported!" << std::endl;
                    } else if (buf == LENS_ONE_SIDED) {
                        double _refIndex;
                        double _radiusH;
                        double _radiusW;
                        double _d;
                        bool _planeIsFront;
                        //Daten aus Datei einlesen
                        importPosition(setupFile, _position);
                        importNormal(setupFile, _normal);
                        importNumber(setupFile, REF_INDEX_OPENING_TAG, _refIndex);
                        importNumber(setupFile, RADIUS_H_OPENING_TAG, _radiusH);
                        importNumber(setupFile, RADIUS_W_OPENING_TAG, _radiusW);
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
                    getContentInBrackets(setupFile,buf);
                } catch (ImporterException e) {
                    throw ImporterException();
                }
            }
            std::cout << "Setup imported!" << std::endl;
        } else {
            std::cerr << "File " + _filename + " doesn't have Setup file Syntax" << std::endl;
        }
    } catch (ImporterException e) {
        std::cerr << e.what() << std::endl;
    }
}

Importer::Importer() {
}




