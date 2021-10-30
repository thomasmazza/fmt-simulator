#include "objectGenerator.hpp"

void ObjectGenerator::generateObject(Config::object& object) {
    //srand(time(NULL));
    for (unsigned int i = 0; i<256; i++){
        Config::objectRow objectRow;
        for(unsigned int j = 0; j<256;j++){
            int wavelength = rand()%800+ 200;
            std::vector<double> position({(double)i,(double)j,0});
            objectRow.push_back(objectPoint(position,wavelength));
        }
     object.push_back(objectRow);
    }
}

void ObjectGenerator::generateRainbow(Config::object& object) {
    int wavelength = 380;
    for (unsigned int i = 0; i<256; i++){
        Config::objectRow objectRow;
        for(unsigned int j = 0; j<256;j++){
            std::vector<double> position({(double)i,(double)j,0});
            objectRow.push_back(objectPoint(position,wavelength));
        }
     object.push_back(objectRow);
        wavelength += 1.56;
    }
}
