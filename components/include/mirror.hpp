#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "component.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

class Mirror: public Component {
    private:

    public:
        Mirror(vector&, vector&);
        bool hitComponent(Photon&);
        vector getOutDir(Photon&);
};
