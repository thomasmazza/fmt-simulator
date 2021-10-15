#pragma once

#include "../../photon/include/photon.hpp"
#include "component.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

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
        bool getOutDir(Photon&);
        static std::string getType();
};
