#pragma once

#include "componentType.hpp"
#include <vector>
#include "../../utils/include/operators.hpp"

class Component {
    protected:
        std::vector<double> position;
        std::vector<double> normal;
        const ComponentType type;
    public:
        Component(std::vector<double>& position, std::vector<double>& normal, ComponentType type);
        Component( const Component& component);
        const std::vector<double>& getPosition();
        void setPosition(std::vector<double>&);
        const std::vector<double>& getNormal();
        void setNormal(std::vector<double>&);
        const ComponentType &getType();

};
