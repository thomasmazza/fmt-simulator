#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include "../include/utils.hpp"
#include <boost/numeric/ublas/io.hpp>
#include "../include/component.hpp"
//#include "filter.hpp"
//#include "mirror.hpp"
#include "../include/detector.hpp"

//#include "mirrorElliptical.hpp"
#include "../../photon/include/photon.hpp"
//#include "mirrorRectangle.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;

int main() {
    vector v (3);
    for (int i = 0; i < 3; i++) {
        v(i) = 0;
    }
    Photon ph(v, v, 700, 0);
    std::vector<Photon> phV;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            v(0) = j / 10.0;
            v(1) = i / 10.0;
            v(2) = 0;
            ph.setPosition(v);
            v(0) = 0;
            v(1) = 0;
            v(2) = 1;
            ph.setDirection(v);
            phV.push_back(ph);
        }
    }

    v(0) = 0.5;
    v(1) = 0.5;
    v(2) = 5;

    vector vn(3);
    vn(0) = 0;
    vn(1) = 0;
    vn(2) = 5;


    Detector d(v, vn, 50, 0.03);

    for (int i = 0; i < 100; i++) {
        d.getInPoint(phV[i]);
    }



    return 0;

}