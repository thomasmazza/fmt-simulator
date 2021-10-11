#pragma once

#include <string>
#include <fstream>

#include "setupList.hpp"
#include "../../components/include/component.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename std::string string;

namespace setup {
    class Importer {
    private:
        static const string FILTER;
        static const string LENS_ONE_SIDED;
        static const string LENS_TWO_SIDED;
        static const string MIRROR_ELLIPTICAL;
        static const string MIRROR_CIRCLE;
        static const string MIRROR_RECTANGLE;
        static const string MIRROR_SQUARE;
    public:
        Importer();

        static void importPosNorm(std::ifstream &, vector &, vector &);

        static void normalizeVector(vector &);

        static void importStp(List &, std::string);
    };
}
