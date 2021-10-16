
#include <cstdint>

struct BmpFileHeader {
    static const char signature[2];
    uint32_t sizeOfFile;
    static const uint32_t reserved;
    static const uint32_t offset;
    BmpFileHeader(unsigned int&, unsigned int&);
};
