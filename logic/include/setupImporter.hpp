#pragma once

#include <string>
#include <fstream>

#include "setupList.hpp"
#include "../../components/include/component.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

namespace setup {
    class Importer {
    private:
    public:
        Importer();
        static void importPosNorm(std::ifstream&, vector&, vector&);
        static void normalizeVector(vector&);
        static void importStp(List&, std::string);
    };
}
