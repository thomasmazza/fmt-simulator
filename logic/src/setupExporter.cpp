#include <fstream>

#include "../include/setupExporter.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

namespace setup {
    void Exporter::exportStp(List& _lst, string _filename) {
        std::ofstream dataOut(_filename, std::ios::out);
        dataOut << "[";
        for(int i = 0; i < _lst.getLength(); i++) {
            //Klassentyp eintragen
            std::string className = _lst.elem(i)->getType();
            dataOut << className << "]" << '\n';
            //Position und Normale in Datei eintragen
            vector _pos = _lst.elem(i)->getPosition();
            dataOut << _pos(0) << " " << _pos(1) << " " << _pos(2) << '\n';
            vector _normal = _lst.elem(i)->getNormal();
            dataOut << _normal(0) << " " << _normal(1) << " " << _normal(2) << '\n';
            switch(className) {
                case "Filter":
                    dataOut << _lst.elem(i)->getLowerLimit() << '\n' << _lst.elem(i)->getUpperLimit() << '\n' << '\n';
                    break;
                case "LensOneSided":
                    dataOut << _lst.elem(i)->getRefIndex() << '\n' << _lst.elem(i)->getRadiusH() << '\n'
                    << _lst.elem(i)->getRadiusW() << '\n' << _lst.elem(i)->getPlaneIsFront() << '\n' << '\n';
                    break;
                case "LensTwoSided":
                    dataOut << _lst.elem(i)->getRefIndex() << '\n' << _lst.elem(i)->getRadiusH() << '\n'
                    << _lst.elem(i)->getRadiusI() << '\n' << _lst.elem(i)->getRadiusO() << '\n' << '\n';
                    break;
                case "MirrorElliptical":
                case "MirrorCircle":
                    dataOut << _lst.elem(i)->getRH() << '\n' << _lst.elem(i)->getRH() << '\n' << '\n';
                case "MirrorRectangle":
                case "MirrorSquare":
                    dataOut << _lst.elem(i)->getLengthH() << '\n' << _lst.elem(i)->getLengthW() << '\n' << '\n';
                default:
                    break;
            }
        }
        dataOut.close();
    }

    Exporter::Exporter() {
        //TODO: Nothing
    }
}
