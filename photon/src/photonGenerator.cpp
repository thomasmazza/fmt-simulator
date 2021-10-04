#include "photonGenerator.hpp"
#include <time.h>
#include <stdlib.h>
#include "../../utils/include/utils.hpp"

PhotonGenerator::PhotonGenerator(objectPoint _raster[65536]){
    for(int i =0; i < 65536; i++) {
        raster[i] = _raster[i];
    }
}

Photon PhotonGenerator::generatePhoton() {
    srand(time(NULL));
    int pointSelector = rand()%65536;
    vector randomDirection(3);
    for (int i = 0; i < randomDirection.size();i++){
        randomDirection(i) = rand() % 1000;
    }
    Utils::normalizeVector(randomDirection);
    vector position = raster[pointSelector].getPosition();
    int wavelength = raster[pointSelector].getWavelength();
    int intensity = rand()%100 +1;

    return Photon(position, randomDirection, wavelength, intensity);
}
