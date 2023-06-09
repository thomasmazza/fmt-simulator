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
#include "detector.hpp"
#include "aperture.hpp"

#include "componentType.hpp"
#include "config.hpp"

class Exporter {
private:
    static void exportInBrackets(std::ofstream& os, const std::string &content);
    static void exportInBrackets(std::ofstream& os, const ComponentType type);
    static void exportInClosingBrackets(std::ofstream& os, const std::string &content);
    static void exportInClosingBrackets(std::ofstream& os, const ComponentType type);
    static void exportVector(std::ofstream& os, const std::vector<double> &_vector);
    static void exportParameter(std::ofstream& os, std::string parameterTag, int number);
    static void exportParameter(std::ofstream& os, std::string parameterTag, double number);
public:
    static void exportStp(List &, std::string);
    static void exportObject(Config::object & object, std::string filename);
    static void exportBMPImage( Detector&, std::string filename);
};

