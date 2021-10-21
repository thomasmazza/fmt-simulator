#include "bmpFileHeader.hpp"
#include "bmpInfoHeader.hpp"

BmpFileHeader::BmpFileHeader(const int _width, const int _height) {
    reserved1 = 0;
    reserved2 = 0;
    sizeOfFile = 2 + sizeof(BmpFileHeader) + sizeof(BmpInfoHeader) + _width * _height * 3;
    offsetBits = 0x36;
}