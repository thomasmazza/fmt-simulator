#include "bmpInfoHeader.hpp"
#include <cstdint>


BmpInfoHeader::BmpInfoHeader(unsigned int & _width, unsigned int & _height) {
    sizeOfThisHeader = 40;
    width = _width;
    height = _height;
    numberOfColorPlanes = 1;
    colorDepth = 24;
    compressionMethod = 0;
    rawBitmapDataSize = 0;
    horizontalResolution = 3780;
    verticalResolution = 3780;
    colorTableEntries = 0;
    importantColors = 0;
}