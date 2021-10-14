#pragma once

#include <string>

#include "setupList.hpp"
#include "../../components/include/component.hpp"

#include "filter.hpp"
#include "lensOneSided.hpp"
#include "lensTwoSided.hpp"
#include "mirrorCircle.hpp"
#include "mirrorSquare.hpp"
#include "mirrorRectangle.hpp"
#include "mirrorElliptical.hpp"

class Exporter {
private:
public:
    Exporter();

    static void exportStp(List &, std::string);
};

