#include "photonGenerator.hpp"
#include <time.h>
#include <stdlib.h>
#include "../../utils/include/utils.hpp"

PhotonGenerator::PhotonGenerator(std::vector<objectPoint> _raster):raster(_raster){
}


Photon PhotonGenerator::generatePhoton() {
    srand(time(NULL));
    int pointSelector = rand()%65536;
    std::vector<double> randomDirection(3);
    for (int i = 0; i < randomDirection.size();i++){
        randomDirection[i] =(double) (rand() % 1000);
        randomDirection[i] = rand()%1?-randomDirection[i]:randomDirection[i];
    }
    Utils::normalizeVector(randomDirection);
    std::vector<double> position = raster[pointSelector].getPosition();
    int wavelength = raster[pointSelector].getWavelength();
    int intensity = rand()%100 +1;

    return Photon(position, randomDirection, wavelength, intensity);
}
