#pragma once

#include <vector>
#include "../../photon/include/photon.hpp"
#include "../../photon/include/photonGenerator.hpp"
#include "../../components/include/component.hpp"
#include "operators.hpp"
#include "setupList.hpp"
#include "filter.hpp"
#include "lensTwoSided.hpp"
#include "lensOneSided.hpp"
#include "mirrorRectangle.hpp"
#include "mirrorCircle.hpp"
#include "mirrorElliptical.hpp"
#include "mirrorSquare.hpp"
#include "detector.hpp"
#include "aperture.hpp"
#include "config.hpp"
#include "componentType.hpp"
#include "optim.hpp"

#include <QProgressBar>

namespace simulation{
    std::vector<Photon>* startTracing(Config::object &_object, int maxAnzPhot, List* lstComp, QProgressBar*);
    std::vector<Photon>* startTracing2(Config::object &_object, int maxAnzPhot, List* lstComp);
    void doStuff(short _bright,short _focus,short _doF, Config::object &_object, List* lstComp, std::vector<Photon>* lstPhotonHit);
    int optTracing(List* , std::vector<Photon>*);
    double getDof(List*);
}
