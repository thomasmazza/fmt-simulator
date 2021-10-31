#include <iostream>
#include <fstream>

#include "setupList.hpp"
#include "../include/importer.hpp"
#include "../include/exporter.hpp"
#include "objectGenerator.hpp"


int main() {
    setlocale(LC_ALL, "C");
   /* std::cout << "LC_ALL: " << setlocale(LC_ALL, NULL) << std::endl;
    std::cout << "LC_CTYPE: " << setlocale(LC_CTYPE, NULL) << std::endl;*/
    std::cout << std::stod("5.431") << std::endl;
    /*
    List *testList = new List();
    List *testList1 = new List();
    int thisI = 5000;
    Importer::importStp(*testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/setup.xml");

    Exporter::exportStp(*testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport.xml");
    Importer::importStp(*testList1, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport.xml");
    Exporter::exportStp(*testList1, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport1.xml");
*/
    Config::object _object;
    _object.clear():
//    ObjectGenerator::generateObject(_object);
//    Exporter::exportObject(_object, "/home/thomas/CLionProjects/fmt-simulator/logic/src/object.xml");
//    PhotonGenerator photonGenerator(_object);
//    Photon testPhoton = photonGenerator.generatePhoton();
//    std::cout << testPhoton.getPosition()[0] << " " << testPhoton.getPosition()[1] << " " <<  testPhoton.getPosition()[2] << std::endl;
//    std::cout << testPhoton.getWaveLength() << std::endl;
//    std::cout << testPhoton.getDirection()[0] << " " << testPhoton.getDirection()[1] << " " <<  testPhoton.getDirection()[2] << std::endl;
}
