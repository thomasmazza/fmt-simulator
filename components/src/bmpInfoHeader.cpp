#include "bmpInfoHeader.hpp"
#include <cstdint>

const uint32_t BmpInfoHeader::sizeOfThisHeader = 40;
const uint16_t BmpInfoHeader::numberOfColorPlanes = 1;
const uint16_t BmpInfoHeader::colorDepth = 24;
const uint32_t BmpInfoHeader::compressionMethod = 0;
const uint32_t BmpInfoHeader::rawBitmapDataSize = 0;
const int32_t BmpInfoHeader::horizontalResolution = 3780;
const int32_t BmpInfoHeader::verticalResolution = 3780;
const uint32_t BmpInfoHeader::colorTableEntries = 0;
const uint32_t BmpInfoHeader::importantColors = 0;

BmpInfoHeader::BmpInfoHeader(unsigned int & _width, unsigned int & _height) {
    width = _width;
    height = _height;
}