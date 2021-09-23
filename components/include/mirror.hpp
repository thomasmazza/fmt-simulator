#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include "component.hpp"
#include "photon.hpp"
#include "math.h"

typedef typename boost::numeric::ublas::vector<double> vector;

class Mirror: public Component {
    private:

    public:
        Mirror(vector&, vector&);
        virtual bool hitComponent(Photon&)=0;
        virtual vector getOutDir(Photon&)=0;
};
