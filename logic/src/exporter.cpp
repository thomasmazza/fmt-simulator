#include <fstream>

#include "../include/exporter.hpp"
#include "importer.hpp"

using namespace Config;
std::ostream& operator <<(std::ostream& os, ComponentType _type){
    switch(_type){
        case filter : os << "Filter"; break;
        case lensOneSided : os << "LensOneSided"; break;
        case lensTwoSided : os << "LensTwoSided"; break;
        case mirrorRectangle : os << "MirrorRectangle"; break;
        case mirrorSquare : os << "MirrorSquare"; break;
        case mirrorElliptical : os << "MirrorElliptical"; break;
        case mirrorCircle : os << "MirrorCircle"; break;
        default : os.setstate(std::ios_base::failbit);
    }
    return os;
}

void Exporter::exportInBrackets(std::ofstream &os, const std::string &content) {
    os << "<" << content << ">" << std::endl;
}

void Exporter::exportInBrackets(std::ofstream &os, const ComponentType type) {
    os << "<" << type << ">" << std::endl;
}

void Exporter::exportInClosingBrackets(std::ofstream &os, const std::string &content) {
    os << "</" << content << ">" << std::endl;
}

void Exporter::exportInClosingBrackets(std::ofstream &os, const ComponentType type) {
    os << "</" << type << ">" << std::endl;
}

void Exporter::exportVector(std::ofstream &os, const std::vector<double> &_vector) {
    os << _vector[0] << " " << _vector[1] << " " << _vector[2] << std::endl;
}

void Exporter::exportParameter(std::ofstream &os, std::string parameterTag,int number) {
    exportInBrackets(os, parameterTag);
    os << number << std::endl;
    exportInClosingBrackets(os, parameterTag);
}

void Exporter::exportStp(List &_lst, std::string _filename) {
    std::ofstream dataOut(_filename, std::ios::out);
    exportInBrackets(dataOut, SETUP_OPENING_TAG);
    for (int i = 0; i < _lst.getLength(); i++) {
        //Klassentyp eintragen
        ComponentType className = _lst.elem(i)->getType();
        exportInBrackets(dataOut, className);
        //Position und Normale in Datei eintragen
        exportInBrackets(dataOut, POSITION_OPENING_TAG);
        exportVector(dataOut, _lst.elem(i)->getPosition());
        exportInBrackets(dataOut, POSITION_CLOSING_TAG);
        exportInBrackets(dataOut, NORMAL_OPENING_TAG);
        exportVector(dataOut, _lst.elem(i)->getPosition());
        exportInBrackets(dataOut, NORMAL_CLOSING_TAG);
        switch (className) {
            case filter:
                exportParameter(dataOut, LOWER_LIMIT_OPENING_TAG, static_cast<Filter &>(*_lst.elem(i)).getLowerLimit());
                exportParameter(dataOut, UPPER_LIMIT_OPENING_TAG, static_cast<Filter &>(*_lst.elem(i)).getUpperLimit());
                break;
            case lensOneSided:
                exportParameter(dataOut, N_OPENING_TAG, static_cast<LensOneSided&>(*_lst.elem(i)).getN());
                exportParameter(dataOut, RADIUS_H_OPENING_TAG, static_cast<LensOneSided&>(*_lst.elem(i)).getRadiusH());
                exportParameter(dataOut, RADIUS_W_OPENING_TAG, static_cast<LensOneSided&>(*_lst.elem(i)).getRadiusW());
                exportParameter(dataOut, D_OPENING_TAG, static_cast<LensOneSided&>(*_lst.elem(i)).getD());
                exportParameter(dataOut, PLANE_IS_FRONT_OPENING_TAG, static_cast<LensOneSided&>(*_lst.elem(i)).getPlaneIsFront());
                break;
            case lensTwoSided:
                exportParameter(dataOut, N_OPENING_TAG, static_cast<LensTwoSided&>(*_lst.elem(i)).getN());
                exportParameter(dataOut, RADIUS_H_OPENING_TAG, static_cast<LensTwoSided&>(*_lst.elem(i)).getRadiusH());
                exportParameter(dataOut, RADIUS_I_OPENING_TAG, static_cast<LensTwoSided&>(*_lst.elem(i)).getRadiusI());
                exportParameter(dataOut, RADIUS_O_OPENING_TAG, static_cast<LensTwoSided&>(*_lst.elem(i)).getRadiusO());
                exportParameter(dataOut, D_OPENING_TAG, static_cast<LensTwoSided&>(*_lst.elem(i)).getD());
                break;
            case mirrorElliptical:
                exportParameter(dataOut, RADIUS_H_OPENING_TAG,static_cast<MirrorElliptical &>(*_lst.elem(i)).getRadiusH());
                exportParameter(dataOut, RADIUS_W_OPENING_TAG,static_cast<MirrorElliptical &>(*_lst.elem(i)).getRadiusW());
                break;
            case mirrorCircle:
                exportParameter(dataOut, RADIUS_OPENING_TAG, static_cast<MirrorCircle &>(*_lst.elem(i)).getRadius());
                break;
            case mirrorRectangle:
                exportParameter(dataOut, LENGTH_H_OPENING_TAG,static_cast<MirrorRectangle &>(*_lst.elem(i)).getLengthH());
                exportParameter(dataOut, LENGTH_W_OPENING_TAG, static_cast<MirrorRectangle &>(*_lst.elem(i)).getLengthW());
                break;
            case mirrorSquare:
                exportParameter(dataOut, LENGTH_OPENING_TAG, static_cast<MirrorSquare &>(*_lst.elem(i)).getLength());
                break;
            default:
                break;
        }
        exportInClosingBrackets(dataOut, className);
    }
    exportInBrackets(dataOut, SETUP_CLOSING_TAG);
    dataOut.close();
}

void Exporter::exportObject(Config::object &object, std::string filename) {
    std::ofstream dataOut(filename, std::ios::out);
    exportInBrackets(dataOut, OBJECT_OPENING_TAG);
    for(Config::objectRow row: object){
        exportInBrackets(dataOut, OBJECT_ROW_OPENING_TAG);
        for(objectPoint point: row){
            exportInBrackets(dataOut, POINT_OPENING_TAG);
            exportInBrackets(dataOut, POSITION_OPENING_TAG);
            exportVector(dataOut,point.getPosition());
            exportInBrackets(dataOut, POSITION_CLOSING_TAG);
            exportInBrackets(dataOut, WAVELENGTH_OPENING_TAG);
            dataOut << point.getWavelength() << std::endl;
            exportInBrackets(dataOut, WAVELENGTH_CLOSING_TAG);
            exportInBrackets(dataOut, POINT_CLOSING_TAG);
        }
        exportInBrackets(dataOut, OBJECT_ROW_CLOSING_TAG);
    }
    exportInBrackets(dataOut, OBJECT_CLOSING_TAG);
    dataOut.close();
}
