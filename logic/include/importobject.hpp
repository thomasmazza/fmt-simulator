#pragma once

#include "objectPoint.hpp"

#include <iostream>

class ObjectImporter {
private:
    const std::string OBJECT_OPENING_TAG = "<object>";
    const std::string OBJECT_CLOSING_TAG = "</object>";
    const std::string NAME_OPENING_TAG = "<name>";
    const std::string NAME_CLOSING_TAG = "</name>";
    const std::string POINT_OPENING_TAG = "<point>";
    const std::string POINT_CLOSING_TAG = "</point>";
    const std::string POSITION_OPENING_TAG = "<position>";
    const std::string POSITION_CLOSING_TAG = "</position>";
    const std::string WAVELENGTH_OPENING_TAG = "<wavelength>";
    const std::string WAVELENGTH_CLOSING_TAG = "</wavelength>";
    std::string name = "undefined";

public:
    static std::vector<objectPoint> importObject(std::string);
    void setName();
};