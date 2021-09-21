#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "component.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

class Lens: public Component {
protected:
    double refIndex;
    double radiusH;
public:
    Lens(vector&, vector&, double, double);
    bool hitComponent(Photon&);
    virtual vector getOutDir(Photon&)=0;
};