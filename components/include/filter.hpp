#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "component.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

class Filter : public Component {
    private:
        int lowerLimit;
        int upperLimit;
    public:
        Filter(vector&, vector&, int, int);
        int getLowerLimit();
        void setLowerLimit(int);
        int getUpperLimit();
        void setUpperLimit(int);
        bool inRange(int);
        static std::string getType();
};
