#pragma once

#include "cstdint"

struct BmpInfoHeader
{
    unsigned int sizeInfoHeader;
    int width;
    int height;
    unsigned short colorPlanes;
    unsigned short bitCount;
    unsigned int compression;
    unsigned int sizeImageData;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    unsigned int colorsUsed;
    unsigned int importantColors;
    BmpInfoHeader(int, int);
};
