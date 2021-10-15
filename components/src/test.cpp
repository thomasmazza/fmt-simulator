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
#include "rgb.hpp"
#include "../../photon/include/photon.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename boost::numeric::ublas::vector<RGB> rgb_vector;

int main() {
    vector v (3);
    for (int i = 0; i < 3; i++) {
        v(i) = 0;
    }
    Photon ph(v, v, 700, 0);
    std::vector<Photon> phV;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
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
    v(2) = 5.0;

    vector vn(3);
    vn(0) = 0.0;
    vn(1) = 0.0;
    vn(2) = 5.0;

    vector vpe(3);
    vpe(0) = 0.5;
    vpe(1) = 1.0;
    vpe(2) = 5.0;

    vector vpc(3);
    vpc(0) = 0.5;
    vpc(1) = 0.5;
    vpc(2) = 0.0;

    Detector d(v, vn, vpe, vpc, 50.0, 0.03);

    for (int i = 0; i < 100; i++) {
        d.getInPoint(phV[i]);
    }
    rgb_vector image = d.createImage();
   /* for (int i = 0; i < 100; i++) {
        std::cout << image[i].r << " " << image[i].g << " " << image[i].b << std::endl;
    }
*/

    return 0;

}