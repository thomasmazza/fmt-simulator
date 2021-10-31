#include "bmpFileHeader.hpp"
#include "bmpInfoHeader.hpp"

/**
 * @brief Constructor for the file header
 * @param _width Width of image in pixels
 * @param _height Height of image in pixels
 */
BmpFileHeader::BmpFileHeader(int _width, int _height) {
    reserved1 = 0;
    reserved2 = 0;
    sizeOfFile = 2 + sizeof(BmpFileHeader) + sizeof(BmpInfoHeader) + _width * _height * 3;
    offsetBits = 0x36;
}
