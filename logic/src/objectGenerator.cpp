#include "objectGenerator.hpp"

const void ObjectGenerator::generateObject(Config::object& object) {
    for (unsigned int i = 0; i<256; i++){
        Config::objectRow objectRow;
        for(unsigned int j = 0; j<256;j++){
            srand(time(NULL));
            int wavelength = rand()%800+ 200;
            std::vector<double> position({(double)i,(double)j,0});
            objectRow.push_back(objectPoint(position,wavelength));
        }
     object.push_back(objectRow);
    }
}
