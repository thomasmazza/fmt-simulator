#include<iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "component.hpp"
#include "filter.hpp"
#include "mirror.hpp"
#include "mirrorElliptical.hpp"
#include "../../photon/include/photon.hpp"
#include "mirrorRectangle.hpp"
#include "detector.hpp"

int main() {
    vector testVector(3);
    for (unsigned i = 0; i < testVector.size(); i++) {
        testVector(i) = i;
    }
    Filter filter1(testVector, testVector, 1, 1);
    std::cout << filter1.getLowerLimit() << '\n';
    Component component1(testVector, testVector);
    vector test = component1.getPosition();
    //MirrorRectangle lb = MirrorRectangle(testVector, testVector, 1, 1);
    std::cout << test << '\n';
    MirrorElliptical la = MirrorElliptical(testVector, testVector, 1, 1);
    Photon testPhoton(testVector, testVector, 600, 500);
    std::cout << la.hitComponent(testPhoton, testVector) << '\n';


    return 0;
}