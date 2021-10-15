#pragma once

#include <string>

#include <boost/numeric/ublas/vector.hpp>

#include "setupList.hpp"
#include "../../components/include/component.hpp"

#include "filter.hpp"
#include "lensOneSided.hpp"
#include "lensTwoSided.hpp"
#include "mirrorCircle.hpp"
#include "mirrorSquare.hpp"
#include "mirrorRectangle.hpp"
#include "mirrorElliptical.hpp"

#include "componentType.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
class Exporter {
private:
    static void exportInBrackets(std::ofstream& os, const std::string &content);
    static void exportInBrackets(std::ofstream& os, const ComponentType type);
    static void exportInClosingBrackets(std::ofstream& os, const std::string &content);
    static void exportInClosingBrackets(std::ofstream& os, const ComponentType type);
    static void exportVector(std::ofstream& os, const vector &_vector);
    static void exportParameter(std::ofstream& os, std::string parameterTag, int number);
public:
    Exporter();
    static void exportStp(List &, std::string);
};

