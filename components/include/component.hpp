#pragma once

#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;

class Component {
    protected:
        vector position;
        vector normal;
    public:
        Component(vector& position,vector& normal);
        vector getPosition();
        void setPosition(vector&);
        vector getNormal();
        void setNormal(vector&);
};
