#include <cstdint>


/**
 * @brief Creates file header for .bmp format
 */
struct BmpFileHeader {
    unsigned int sizeOfFile;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offsetBits;
    BmpFileHeader(int, int);
};
