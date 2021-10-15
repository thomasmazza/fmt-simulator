#include "../include/pixel.hpp"
#include "../include/rgb.hpp"

Pixel::Pixel() {
    RGB black;
    bucket[0] = black;
}

Pixel::Pixel(const Pixel& obj) {
    bucket = obj.bucket;
}


