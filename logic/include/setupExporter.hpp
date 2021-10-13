#pragma once

#include <string>

#include "setupList.hpp"
#include "../../components/include/component.hpp"


class Exporter {
private:
public:
    Exporter();

    static void exportStp(List &, std::string);
};

