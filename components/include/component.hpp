#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "componentType.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

class Component {
    protected:
        vector position;
        vector normal;
        const ComponentType type;
    public:
        Component(vector& position, vector& normal, ComponentType type);
        const vector& getPosition();
        void setPosition(vector&);
        const vector& getNormal();
        void setNormal(vector&);
        const ComponentType &getType();
};
