#pragma once

#include "component.hpp"
#include "../../photon/include/photon.hpp"
#include "math.h"


class Mirror: public Component {
    public:
        Mirror(std::vector<double>&, std::vector<double>&, ComponentType _type);
        virtual bool hitComponent(Photon&, std::vector<double>&)=0;
        virtual bool getOutDir(Photon&, std::vector<double>&, std::vector<double>&)=0;
};
