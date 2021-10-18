#include <iostream>
#include <fstream>

#include "setupList.hpp"
#include "../include/importer.hpp"
#include "../include/exporter.hpp"
#include "objectGenerator.hpp"
#include "photonGenerator.hpp"

int main() {
    List testList = List();
    List testList1 = List();
    Importer::importStp(testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/setup.xml");
    Exporter::exportStp(testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport.xml");
    Importer::importStp(testList1, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport.xml");
    Exporter::exportStp(testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport1.xml");
//    Config::object _object;
//    ObjectGenerator::generateObject(_object);
//    Exporter::exportObject(_object, "/home/thomas/CLionProjects/fmt-simulator/logic/src/object.xml");
//    PhotonGenerator photonGenerator(_object);
//    Photon testPhoton = photonGenerator.generatePhoton();
//    std::cout << testPhoton.getPosition()[0] << " " << testPhoton.getPosition()[1] << " " <<  testPhoton.getPosition()[2] << std::endl;
//    std::cout << testPhoton.getWaveLength() << std::endl;
//    std::cout << testPhoton.getDirection()[0] << " " << testPhoton.getDirection()[1] << " " <<  testPhoton.getDirection()[2] << std::endl;
}
