#include "photonGenerator.hpp"
#include <time.h>
#include <stdlib.h>
#include "../../utils/include/utils.hpp"

PhotonGenerator::PhotonGenerator(Config::object _raster):raster(_raster){
}


Photon PhotonGenerator::generatePhoton() {
    srand(time(NULL));
    Config::objectRow selectedRow = raster[rand()%raster.size()];
    objectPoint selectedPoint = selectedRow[rand()%selectedRow.size()];
    std::vector<double> randomDirection(3);
    for (int i = 0; i < randomDirection.size();i++){
        randomDirection[i] =(double) (rand() % 1000);
        randomDirection[i] = rand()%1?-randomDirection[i]:randomDirection[i];
    }
    Utils::normalizeVector(randomDirection);
    std::vector<double> position = selectedPoint.getPosition();
    int wavelength = selectedPoint.getWavelength();

    return Photon(position, randomDirection, wavelength);
}
