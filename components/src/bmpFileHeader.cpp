#include "bmpFileHeader.hpp"

BmpFileHeader::BmpFileHeader(unsigned int& size_w, unsigned int & size_h) {
    signature[0] = 'B';
    signature[1] = 'M';
    sizeOfFile = 54 + (size_w * size_h * 3);
    reserved = 0;
    offset = 54;
}