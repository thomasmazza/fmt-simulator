#pragma once

#include <string>

#include "setupList.hpp"
#include "../../components/include/component.hpp"

namespace setup {
    class Exporter {
    private:
    public:
        Exporter();
        static void exportStp(List&, std::string);
    };
}
