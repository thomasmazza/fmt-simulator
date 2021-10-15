#pragma once

#include <vector>
#include "rgb.hpp"

class Pixel {
public:
    std::vector<RGB> bucket;
    Pixel();
    Pixel(const Pixel&);
};