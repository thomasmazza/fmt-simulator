#pragma once

#include <vector>
#include "../../photon/include/photon.hpp"
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
#include "config.hpp"
#include "componentType.hpp"
#include "mainRoutine.hpp"


class Optim {
private:
    std::vector<Photon>* lstPhoton;
    List* lstComp;
    std::vector<double> origin;
    short weightB;
    short weightDoF;
    short weightF;
    int maxPhot;
    Config::object* object;
public:
    Optim(short&, short&, short&, List*, std::vector<Photon>*, Config::object*);//Gewichtung(Hell., Schärfe, Tiefensch.) ; akt. gew.Sum
    void OAimprove();
    void optBright();
    void optFocus();
    void optDoF();
    void startOptim();
    //double calcSum();
};

