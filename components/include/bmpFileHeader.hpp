
#include <cstdint>

struct BmpFileHeader {
    char signature[2];
    uint32_t sizeOfFile;
    uint32_t reserved;
    uint32_t offset;
    BmpFileHeader(unsigned int&, unsigned int&);
};
