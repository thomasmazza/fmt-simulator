#include "importobject.hpp"

static std::vector<objectPoint>ObjectImporter::importObject(std::ifstream &_dataIn) {
    std::string buffer;
    _dataIn >> buffer;
    while(buffer != PICTURE_CLOSING_TAG){
        _dataIn >> buffer

    }

}

void ObjectImporter::setName(std::_name) {
    name = _name;
}
