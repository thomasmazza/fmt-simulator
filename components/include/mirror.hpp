#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "../../utils/include/utils.hpp"
#include "component.hpp"
#include "../../photon/include/photon.hpp"
#include "math.h"

typedef typename boost::numeric::ublas::vector<double> vector;

class Mirror: public Component {
    public:
        Mirror(vector&, vector&);
        virtual bool getOutDir(Photon&, vector&)=0;
        virtual bool calcOut(Photon&, vector&, vector&)=0;
};
