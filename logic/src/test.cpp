#include <iostream>
#include <fstream>
#include "importobject.hpp"

int main() {
     std::string filename("test.xml");
    ObjectImporter::importObject(filename);
}
