#include "bmpFileHeader.hpp"

BmpFileHeader::BmpFileHeader(unsigned int _width, unsigned int _height) {
    signature[0] = {'B'};
    signature[1] = {'M'};
    sizeOfFile = 54 + (_width * _height * 3);
    reserved = 0;
    offset = 54;
}