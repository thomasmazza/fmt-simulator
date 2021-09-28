#pragma once

#include <string>

#include "setupList.hpp"
#include "../../components/include/component.hpp"

namespace setup {
    class Importer {
    private:
    public:
        Importer();
        static void importStp(List&, std::string);
    };
}
