#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include "component.hpp"
#include "../../photon/include/photon.hpp"
#include "math.h"

typedef typename boost::numeric::ublas::vector<double> vector;

class Mirror: public Component {
    public:
        Mirror(vector&, vector&, ComponentType _type);
        virtual bool hitComponent(Photon&, vector&)=0;
        virtual bool getOutDir(Photon&, vector&, vector&)=0;
};
