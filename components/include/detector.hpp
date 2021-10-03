#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "component.hpp"
#include "../../photon/include/photon.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

class Detector: public Component {
protected:
    int size;
    double pixelSize;
    double length;
public:
    Detector(vector&, vector&, int, double);
    bool hitComponent(Photon&);
    vector getInPoint(Photon&);
};
