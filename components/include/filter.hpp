#pragma once

#include "component.hpp"


class Filter : public Component {
    private:
        int lowerLimit;
        int upperLimit;
    public:
        Filter(std::vector<double>&, std::vector<double>&, int, int);
        int getLowerLimit();
        void setLowerLimit(int);
        int getUpperLimit();
        void setUpperLimit(int);
        bool inRange(int);
        static std::string getType();
};
