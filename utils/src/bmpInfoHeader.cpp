#include "bmpInfoHeader.hpp"


BmpInfoHeader::BmpInfoHeader(int _width, int _height) {
    sizeInfoHeader = sizeof(BmpInfoHeader);
    width = _width;
    height = _height;
    colorPlanes = 1;
    bitCount = 24;
    compression = 0;
    sizeImageData = 0;
    xPixelsPerMeter = 5000;
    yPixelsPerMeter = 5000;
    colorsUsed = 0;
    importantColors = 0;
}