#pragma once
#include <unordered_map>
#include "photon.hpp"
#include "../../utils/include/objectPoint.hpp"
#include "config.hpp"
class PhotonGenerator{
private:
    Config::object raster;
public:
    PhotonGenerator(Config::object);
    Photon generatePhoton();
};
