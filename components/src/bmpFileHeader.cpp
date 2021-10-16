#include "bmpFileHeader.hpp"

const char BmpFileHeader::signature[2] = {'B', 'M'};
const uint32_t BmpFileHeader::reserved = 0;
const uint32_t BmpFileHeader::offset = 54;

BmpFileHeader::BmpFileHeader(unsigned int& _width, unsigned int & _height) {
    sizeOfFile = 54 + (_width * _height * 3);
}