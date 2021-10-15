#include <iostream>
#include <fstream>

#include "setupList.hpp"
#include "../include/importer.hpp"
#include "../include/exporter.hpp"
#include "objectGenerator.hpp"

int main() {
    List testList = List();
//    List testList1 = List();
    Importer::importStp(testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/setup.xml");
    Exporter::exportStp(testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport.xml");
//    Importer::importStp(testList1, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport.xml");
//    Exporter::exportStp(testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/testExport1.xml");
    Config::object _object;
    ObjectGenerator::generateObject(_object);
    Exporter::exportObject(_object, "/home/thomas/CLionProjects/fmt-simulator/logic/src/object.xml");
}
