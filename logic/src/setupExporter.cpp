#include <fstream>

#include "../include/setupExporter.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;


void Exporter::exportStp(List &_lst, std::string _filename) {
    std::ofstream dataOut(_filename, std::ios::out);
    for (int i = 0; i < _lst.getLength(); i++) {
        //Klassentyp eintragen
        ComponentType className = _lst.elem(i)->getType();
        dataOut << "[" << className << "]" << '\n';
        //Position und Normale in Datei eintragen
        vector _pos = _lst.elem(i)->getPosition();
        dataOut << _pos(0) << " " << _pos(1) << " " << _pos(2) << '\n';
        vector _normal = _lst.elem(i)->getNormal();
        dataOut << _normal(0) << " " << _normal(1) << " " << _normal(2) << '\n';
        switch (className) {
            case filter:

                dataOut << static_cast<Filter&>(*_lst.elem(i)).getLowerLimit() << '\n' <<static_cast<Filter&>(*_lst.elem(i)).getUpperLimit() << '\n' << '\n';
                break;
            case lensOneSided:
                dataOut <<static_cast<LensOneSided&>(*_lst.elem(i)).getRadiusH() << static_cast<LensOneSided&>(*_lst.elem(i)).getRadiusW() << '\n' << static_cast<LensOneSided&>(*_lst.elem(i)).getPlaneIsFront() << '\n' << '\n';
                break;
            case lensTwoSided:
                dataOut << static_cast<LensTwoSided&>(*_lst.elem(i)).getRefIndex() << '\n' << _lst.elem(i)->getRadiusH() << '\n'
                        << _lst.elem(i)->getRadiusI() << '\n' << _lst.elem(i)->getRadiusO() << '\n' << '\n';
                break;
            case mirrorElliptical:
                dataOut << _lst.elem(i)->getRH() << '\n' << _lst.elem(i)->getRW() << '\n' << '\n';
            case mirrorCircle:
                dataOut << _lst.elem(i)->getRH() << '\n' << '\n';
            case mirrorRectangle:
                dataOut << _lst.elem(i)->getLengthH() << '\n' << _lst.elem(i)->getLengthW() << '\n' << '\n';
            case mirrorSquare:
                dataOut << _lst.elem(i)->getLengthH() << '\n' << '\n';
            default:
                break;
        }
    }
    dataOut.close();
}

Exporter::Exporter() {
}


