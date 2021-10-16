#pragma once

#include "cstdint"

struct BmpInfoHeader {
    static const uint32_t sizeOfThisHeader;
    int32_t width;
    int32_t height;
    static const uint16_t numberOfColorPlanes;
    static const uint16_t colorDepth;
    static const uint32_t compressionMethod;
    static const uint32_t rawBitmapDataSize;
    static const int32_t horizontalResolution;
    static const int32_t verticalResolution;
    static const uint32_t colorTableEntries;
    static const uint32_t importantColors;
    BmpInfoHeader(unsigned int &, unsigned  int &);
};
