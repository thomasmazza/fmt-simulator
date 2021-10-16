#pragma once

#include "cstdint"

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader;
    int32_t width;
    int32_t height;
    uint16_t numberOfColorPlanes;
    uint16_t colorDepth;
    uint32_t compressionMethod;
    uint32_t rawBitmapDataSize;
    int32_t horizontalResolution;
    int32_t verticalResolution;
    uint32_t colorTableEntries;
    uint32_t importantColors;
    BmpInfoHeader(unsigned int &, unsigned  int &);
};
