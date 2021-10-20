#pragma once

#include "../../utils/include/utils.hpp"
#include "component.hpp"
#include "../../photon/include/photon.hpp"
#include "math.h"


class Mirror: public Component {
    public:
        Mirror(std::vector<double>&, std::vector<double>&, ComponentType _type);
        virtual bool getOutDir(Photon&, std::vector<double>&)=0;
        virtual bool calcOut(Photon&, std::vector<double>&, std::vector<double>&)=0;
};
