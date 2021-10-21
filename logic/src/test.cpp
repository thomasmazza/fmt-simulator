#include <iostream>
#include <fstream>

#include "setupList.hpp"
#include "../include/importer.hpp"
#include "../include/exporter.hpp"
#include "objectGenerator.hpp"
#include "mainRoutine.hpp"
#include "photonGenerator.hpp"
#include "detector.hpp"
typedef typename std::vector<BmpRGB> bmp_vector;
using namespace simulation;

int main() {

    List *testList = new List();
    int thisI = 10000;
    Importer::importStp(*testList, "/home/stce/CLionProjects/fmt-simulator/logic/src/setup.xml");
    std::cout<<testList->getLength()<<std::endl;
    Config::object _object;
    ObjectGenerator::generateObject(_object);
    std::vector<Photon> lost;
    std::cout<<lost.size()<<std::endl;
    startTracing(_object, thisI, testList, lost);
    std::cout<<lost.size()<<std::endl;
    int sizeThisPic =  static_cast<Detector &>(*testList->elem(testList->getLength()-1)).getSize();
    bmp_vector image(sizeThisPic*sizeThisPic);
    //image = static_cast<Detector &>(*testList->elem(testList->getLength()-1)).createImage();

    /*
    Exporter::exportStp(*testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport.xml");
    Importer::importStp(*testList1, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport.xml");
    Exporter::exportStp(*testList1, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport1.xml");
     */
//
//    ObjectGenerator::generateObject(_object);
//    Exporter::exportObject(_object, "/home/thomas/CLionProjects/fmt-simulator/logic/src/object.xml");
//    PhotonGenerator photonGenerator(_object);
//    Photon testPhoton = photonGenerator.generatePhoton();
//    std::cout << testPhoton.getPosition()[0] << " " << testPhoton.getPosition()[1] << " " <<  testPhoton.getPosition()[2] << std::endl;
//    std::cout << testPhoton.getWaveLength() << std::endl;
//    std::cout << testPhoton.getDirection()[0] << " " << testPhoton.getDirection()[1] << " " <<  testPhoton.getDirection()[2] << std::endl;
}
