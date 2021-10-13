#include <iostream>
#include <fstream>
#include "importobject.hpp"
#include "setupList.hpp"
#include "filter.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include "setupImporter.hpp"
typedef typename boost::numeric::ublas::vector<double> vector;
int main() {
    List testList = List();
    Importer::importStp(testList, "/home/thomas/CLionProjects/fmt-simulator/logic/src/setup.xml");

}
