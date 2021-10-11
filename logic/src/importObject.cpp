#include "importobject.hpp"


static std::vector<objectPoint> ObjectImporter::importObject(std::string _filename) {
    std::ifstream dataIn(_filename, std::ios::in);
    std::string buffer;
    std::getline(_dataIn, buffer);
    while(buffer != PICTURE_CLOSING_TAG){
        switch(buffer){
            case NAME_CLOSING_TAG:
                std::cout << "Hallo" << '\n';
                break;
        }
    }

}

void ObjectImporter::setName(std::_name) {
    name = _name;
}
