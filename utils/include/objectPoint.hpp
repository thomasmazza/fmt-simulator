#pragma once
#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;
class objectPoint{
private:
    const int wavelength;
    const vector postion;
public:
    const int& getWavelength();
    const vector& getPosition();
    objectPoint(vector&, int&);
};
