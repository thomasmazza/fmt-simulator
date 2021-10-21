#include "bmpInfoHeader.hpp"


BmpInfoHeader::BmpInfoHeader(unsigned int _width, unsigned int _height) {
    sizeOfThisHeader = 40;
    width = _width;
    height = _height;
    numberOfColorPlanes = 1;
    colorDepth = 24;
    compressionMethod = 0;
    rawBitmapDataSize = 0;
    horizontalResolution = 11811;
    verticalResolution = 11811;
    colorTableEntries = 0;
    importantColors = 0;
}