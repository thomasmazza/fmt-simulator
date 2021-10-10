#pragma once

#include "objectPoint.hpp"
class ObjectImporter {
private:
    const std::string PICTURE_OPENING_TAG = "<picture>";
    const std::string PICTURE_CLOSING_TAG = "</picture>";
    const std::string NAME_OPENING_TAG = "<name>";
    const std::string NAME_CLOSING_TAG = "</name>";
    const std::string POINT_OPENING_TAG = "<point>";
    const std::string POINT_CLOSING_TAG = "</point>";
    const std::string POSITION_X_OPENING_TAG = "<positionX>";
    const std::string POSITION_X_CLOSING_TAG = "</positionX>";
    const std::string POSITION_Y_OPENING_TAG = "<positionY>";
    const std::string POSITION_Y_CLOSING_TAG = "</positionY>";
    const std::string POSITION_Z_OPENING_TAG = "<positionZ>";
    const std::string POSITION_Z_CLOSING_TAG = "</positionZ>";
    const std::string RGB_OPENING_TAG = "<RBG>";
    const std::string RGB_CLOSING_TAG = "</RBG>";
    std::string name = "undefined";

public:
    static std::vector<objectpoint> importObject(std::ifstream&);
    void setName();
};