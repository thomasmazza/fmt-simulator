//
// Created by Lasse Alsmeyer on 20.09.21.
//

#include <boost/numeric/ublas/vector.hpp>
#include "component.hpp"

using namespace boost::numeric::ublas;

namespace component {

    template<typename T>
    class Filter : public Component<T> {
    private:
        int lowerLim;
        int upperLim;
    public:
        Filter(vector<T>&,vector<T>&,int,int);
        int getLowerLim();
        void setLowerLim(int);
        int getUpperLim();
        void setUpperLim(int);
        bool inRange(int);
    };
}

#include "src/filter.cpp"
