#include "../include/importer.hpp"
#include <fstream>
#include "../../components/include/filter.hpp"
#include "../../components/include/lensOneSided.hpp"
#include "../../components/include/lensTwoSided.hpp"
#include "../../components/include/mirrorCircle.hpp"
#include "../../components/include/mirrorElliptical.hpp"
#include "../../components/include/mirrorSquare.hpp"
#include "../../components/include/mirrorRectangle.hpp"
#include "../../components/include/aperture.hpp"
#include "detector.hpp"

using namespace Config;

/**
 * @brief Standard Exception for SetupImporter
 */
struct ImporterException : public std::exception {
    const char *what() const throw() {
        return "Error while import Setup";
    }
};

/**
 * @brief Exception for wrong Syntax in Components
 */
struct InvalidComponentException : public ImporterException {
    const char *what() const throw() {
        return "Invalid Component in Setup File";
    }
};

/**
 * @brief Exception if expected tag differs from received tag
 */
struct WrongTagException : public ImporterException {
    const char *what() const throw() {
        return "Wrong Parameter in Component";
    }
};

/**
 * @brief Exception if received content from Setupfile is not a number
 */
struct NotANumberException : public ImporterException {
    const char *what() const throw() {
        return "Not a valid Number";
    }
};

/**
 * @brief Imports position vector from XML file
 * @param _setupFile ImportFilestream
 * @param _position Reference for position vector
 */
void Importer::importPosition(std::ifstream &_setupFile, std::vector<double> &_position) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, POSITION_OPENING_TAG);
        importVector(_setupFile, _position);
        getContentInBrackets(_setupFile, buf, POSITION_CLOSING_TAG);
    } catch (InvalidComponentException &e) {
        std::cerr << e.what() << std::endl << "Error occurred while creating Position Vector" << std::endl;
        throw InvalidComponentException();
    } catch (WrongTagException &e) {
        std::cerr << e.what() << std::endl << "Expected Parameter: " << POSITION_OPENING_TAG << std::endl
                  << "Retrieved Parameter: " << buf << std::endl;
        throw WrongTagException();
    }
}

/**
 * @brief Imports normal vector from XML file
 * @param _setupFile ImportFileStream
 * @param _normal Reference for normal vector
 */
void Importer::importNormal(std::ifstream &_setupFile, std::vector<double> &_normal) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, NORMAL_OPENING_TAG);
        importVector(_setupFile, _normal);
        getContentInBrackets(_setupFile, buf, NORMAL_CLOSING_TAG);
    } catch (InvalidComponentException &e) {
        std::cerr << e.what() << std::endl << "Error occurred while creating Normal Vector" << std::endl;
        throw InvalidComponentException();
    } catch (WrongTagException &e) {
        std::cerr << e.what() << std::endl << "Expected Parameter: " << NORMAL_OPENING_TAG << std::endl
                  << "Retrieved Parameter: " << buf << std::endl;
        throw WrongTagException();
    }
}

/**
 * @brief Imports position of previous component vector from XML file
 * @param _setupFile ImportFileStream
 * @param _normal Reference for normal vector
 */
void Importer::importPosOfPrevComponent(std::ifstream &_setupFile, std::vector<double> &_posOfPrev) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, POSITION_OF_PREVIOUS_COMPONENT_OPENING_TAG);
        importVector(_setupFile, _posOfPrev);
        getContentInBrackets(_setupFile, buf, POSITION_OF_PREVIOUS_COMPONENT_CLOSING_TAG);
    } catch (InvalidComponentException &e) {
        std::cerr << e.what() << std::endl << "Error occurred while creating posOfPrevComponent Vector" << std::endl;
        throw InvalidComponentException();
    } catch (WrongTagException &e) {
        std::cerr << e.what() << std::endl << "Expected Parameter: " << POSITION_OF_PREVIOUS_COMPONENT_OPENING_TAG
                  << std::endl
                  << "Retrieved Parameter: " << buf << std::endl;
        throw WrongTagException();
    }
}

/**
 * @brief Import vector from XML file
 * @param _setupFile ImportFileStream
 * @param _vector Reference for vector
 */
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

/**
 * @brief Import number from XML file
 * @param _setupFile ImportFileStream
 * @param numberTag Expected ParameterTag
 * @param importNumber Reference for number
 */
void Importer::importNumber(std::ifstream &_setupFile, const std::string &numberTag, int &importNumber) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, numberTag);
        _setupFile >> importNumber;
        getContentInBrackets(_setupFile, buf, "/" + numberTag);
    } catch (std::exception &e) {
        std::cerr << "Error while importing number" << std::endl << "Buffer: " + buf << std::endl;
        throw NotANumberException();
    }
}

/**
 * @brief Import number from XML file
 * @param _setupFile ImportFileStream
 * @param numberTag Expected ParameterTag
 * @param importNumber Reference for number
 */
void Importer::importNumber(std::ifstream &_setupFile, const std::string &numberTag, double &importNumber) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, numberTag);
        _setupFile >> importNumber;
        getContentInBrackets(_setupFile, buf, "/" + numberTag);
    } catch (std::exception &e) {
        std::cerr << "Error while importing number" << std::endl << "Buffer: " + buf << std::endl;
        throw NotANumberException();
    }
}
/**
 * @brief Import Bool from XML file
 * @param _setupFile ImportFileStream
 * @param boolTag Expected ParameterTag
 * @param importBool Reference for bool
 */
void Importer::importBool(std::ifstream &_setupFile, const std::string &boolTag, bool &importBool) {
    std::string buf;
    try {
        getContentInBrackets(_setupFile, buf, boolTag);
        _setupFile >> importBool;
        getContentInBrackets(_setupFile, buf, "/" + boolTag);
    } catch (std::exception &e) {
        std::cerr << "Error while importing Bool" << std::endl << "Buffer: " + buf << std::endl;
        throw ImporterException();
    }
}
/**
 * @brief Get Content in <>-Brackets and checks if the Content the expected Content
 * @param file ImportFileStream
 * @param buf buffer for content
 * @param expectedString expected string to check buffer
 */
void Importer::getContentInBrackets(std::ifstream &file, std::string &buf, const std::string expectedString) {
    getContentInBrackets(file, buf);
    if (buf != expectedString) {
        throw WrongTagException();
    }
}
/**
 * @brief Get Content in <>-Brackets
 * @param file ImportFileStream
 * @param buf buffer for content
 */
void Importer::getContentInBrackets(std::ifstream &file, std::string &buf) {
    std::getline(file, buf, '<');
    std::getline(file, buf, '>');
}
/**
 * @brief Imports SetupFile
 * @param _lst List in which the setup gets imported
 * @param _filename Filename
 */
void Importer::importStp(List &_lst, std::string _filename) {
    setlocale(LC_ALL, "C");
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
            } else if (buf == MIRROR_CIRCLE_OPENING_TAG) {
                double _radius;
                //Daten aus Datei einlesen
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, RADIUS_OPENING_TAG, _radius);

                _lst.append<MirrorCircle>(MirrorCircle(_position, _normal, _radius));
                getContentInBrackets(setupFile, buf, MIRROR_CIRCLE_CLOSING_TAG);
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
            } else if (buf == MIRROR_SQUARE_OPENING_TAG) {
                double _length;
                //Daten aus Datei einlesen
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, LENGTH_OPENING_TAG, _length);

                _lst.append<MirrorSquare>(MirrorSquare(_position, _normal, _length));
                getContentInBrackets(setupFile, buf, MIRROR_SQUARE_CLOSING_TAG);
            } else if (buf == DETECTOR_OPENING_TAG) {
                std::vector<double> _posOfPreviousComponent(3);
                int size;
                double length;
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importPosOfPrevComponent(setupFile, _posOfPreviousComponent);
                importNumber(setupFile, SIZE_OPENING_TAG, size);
                importNumber(setupFile, LENGTH_OPENING_TAG, length);

                _lst.append<Detector>(Detector(_position, _normal, _posOfPreviousComponent, size, length));
                getContentInBrackets(setupFile, buf, DETECTOR_CLOSING_TAG);
            } else if (buf == APERTURE_OPENING_TAG) {
                double radius;
                importPosition(setupFile, _position);
                importNormal(setupFile, _normal);
                importNumber(setupFile, RADIUS_OPENING_TAG, radius);

                _lst.append<Aperture>(Aperture(_position, _normal, radius));
                getContentInBrackets(setupFile, buf, APERTURE_CLOSING_TAG);
            } else if (buf == SETUP_CLOSING_TAG) {
                break;
            } else {
                throw InvalidComponentException();
            }
        }
    } catch (ImporterException e) {
        std::cerr << e.what() << std::endl;
    }
    setupFile.close();
}
/**
 * @brief Imports an Object
 * @param _object Object in which the object gets imported
 * @param filename filename
 */
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
                }
            }
            _object.push_back(rowBuffer);
            getContentInBrackets(setupFile, buf);
        }
    } catch (std::exception &e) {
        std::cerr << "Error while importing Object" << std::endl;
    }
}



