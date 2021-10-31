#include "../include/optim.hpp"
#include "../../utils/include/utils.hpp"
#include <cmath>

void Optim::OAimprove(){
    //Optimierung über versetzen der Komponenten auf die optische Achse mit Abstand von davor
    std::vector<double> origin(3);
    origin[0]=128;
    origin[1]=128;
    origin[2]=0;
    std::vector<double> curDir = lstComp->elem(0)->getPosition();
    curDir = curDir - origin;
    Utils::normalizeVector(curDir);
    Photon phot1(origin, curDir, 550);
    for(int i = 1; i<lstComp->getLength(); i++) {
        ComponentType className = lstComp->elem(i-1)->getType();
        switch (className) {
            case filter:
                static_cast<Filter&>(*lstComp->elem(i-1)).getOutDir(phot1);
                break;
            case lensOneSided:
                static_cast<LensOneSided&>(*lstComp->elem(i-1)).getOutDir(phot1);
                break;
            case lensTwoSided:
                static_cast<LensTwoSided&>(*lstComp->elem(i-1)).getOutDir(phot1);
                break;
            case mirrorElliptical:
                static_cast<MirrorElliptical&>(*lstComp->elem(i-1)).getOutDir(phot1, curDir);
                break;
            case mirrorCircle:
                static_cast<MirrorCircle&>(*lstComp->elem(i-1)).getOutDir(phot1, curDir);
                break;
            case mirrorRectangle:
                static_cast<MirrorRectangle&>(*lstComp->elem(i-1)).getOutDir(phot1, curDir);
                break;
            case mirrorSquare:
                static_cast<MirrorSquare&>(*lstComp->elem(i-1)).getOutDir(phot1, curDir);
                break;
            case detector:
                static_cast<Detector&>(*lstComp->elem(i-1)).getInPoint(phot1);
                break;
            default:
                break;
        }
        std::vector<double> curPos =  lstComp->elem(i-1)->getPosition();
        std::vector<double> nextPos = lstComp->elem(i)->getPosition();
        std::vector<double> diff = nextPos - curPos;
        double abs = Utils::getAbs(diff);
        switch (className) {
            case lensTwoSided:
                abs = abs-static_cast<LensTwoSided&>(*lstComp->elem(i-1)).getD();
                break;
            default:
                break;
        }

        nextPos = phot1.getPosition() + abs*phot1.getDirection();
        lstComp->elem(i)->setPosition(nextPos);
        curDir = nextPos - curPos;
        Utils::normalizeVector(curDir);
    }
    std::cout<<"Im done with the OA-Opt"<<std::endl;
}

void Optim::optBright(){
    //TODO: Optimerung über Filter, Grenzen anpassen bis zu einem gewissen Level
    int noLoops;
    for(int i=lstComp->getLength()-1; i>=0; i--){
        ComponentType className = lstComp->elem(i)->getType();
        switch (className) {
            case filter:
            {
                int uLP = static_cast<Filter&>(*lstComp->elem(i)).getUpperLimit();
                int lLP = static_cast<Filter&>(*lstComp->elem(i)).getLowerLimit();

                static_cast<Filter&>(*lstComp->elem(i)).setUpperLimit(1000);
                static_cast<Filter&>(*lstComp->elem(i)).setLowerLimit(250);
                std::vector<Photon>* optimum = simulation::startTracing2(*object, lstPhoton->size()*1.5, lstComp);

                int sizePost, optimumSize;
                optimumSize = optimum->size();
                double newMin = calcSum();

                static_cast<Filter&>(*lstComp->elem(i)).setUpperLimit(uLP);
                static_cast<Filter&>(*lstComp->elem(i)).setLowerLimit(lLP);

                while (optimumSize - sizePost > 10  && (curMin-newMin)>0){
                    noLoops++;
                    std::vector<Photon>* sizeComp2 = new std::vector<Photon>();
                    if(static_cast<Filter&>(*lstComp->elem(i)).getUpperLimit() <1000 || static_cast<Filter&>(*lstComp->elem(i)).getLowerLimit()>250){
                        if(static_cast<Filter&>(*lstComp->elem(i)).getLowerLimit()>250){
                            lLP--;
                            static_cast<Filter&>(*lstComp->elem(i)).setLowerLimit(lLP);
                        }
                        if(static_cast<Filter&>(*lstComp->elem(i)).getUpperLimit() <1000){
                            uLP++;
                            static_cast<Filter&>(*lstComp->elem(i)).setUpperLimit(uLP);
                        }
                        sizePost = simulation::optTracing(lstComp, optimum);
                        newMin = calcSum();
                    }else{
                        sizePost = optimumSize;
                    }
                }
                curMin = newMin;
                break;
            }
            default:
                break;
        }
    }
    std::cout<<"Done with the BrightOpt: "<<calcSum()<<"with : "<<noLoops<<std::endl;
}

void Optim::optFocus(){
    //Optimierung über einen BP und Abstand von ankommenden Photonen auf dem Detektor
    for(int i=lstComp->getLength()-1; i>=0; i--){
        ComponentType className = lstComp->elem(i)->getType();
        switch (className) {
            case lensTwoSided:
                if(true){
                    //Zuerst Detektor auf Brennweite setzen als vorkond.
                    std::vector<double> diff = (lstComp->elem(i+1)->getPosition())-(lstComp->elem(i-1)->getPosition());
                    double abs = Utils::getAbs(diff);
                    Utils::normalizeVector(diff);
                    double d = static_cast<LensTwoSided&>(*lstComp->elem(i)).getD();
                    abs = abs - d;
                    std::vector<double> newPos(3);


                    double step=abs/50;
                    double prev, post, newRes, difference = 200;
                    double newSum1;
                    double newSum2;
                    std::vector<double> positivePos(3);
                    std::vector<double> negativPos(3);
                    double curRes;
                    double funcCalls=0;
                    double curMini = 1000000;
                    std::vector<double> curMinVec(3);
                    std::vector<double> cur = lstComp->elem(i-1)->getPosition();
                    double absCur;


                    for(int j=0; j<50; j++){
                        std::vector<double> next = cur + (step*j)*diff;
                        static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(next);
                        simulation::optTracing(lstComp, lstPhoton);
                        double q = calcSum();
                        std::cout<<q<<std::endl;
                        if(q<curMini){
                            absCur = (step*j);
                            curMini = q;
                            curMinVec = next;
                        }
                    }
                    newPos = curMinVec;
                    lstComp->elem(i)->setPosition(newPos);

                    while (difference > 0.0001 && absCur>0) {
                        //Berechne Gradienten
                        simulation::optTracing(lstComp, lstPhoton);
                        curRes = calcSum();
                        funcCalls++;
                        positivePos = newPos + step*diff;
                        negativPos = newPos - step*diff;

                        static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(positivePos);
                        simulation::optTracing(lstComp, lstPhoton);
                        post = calcSum();

                        static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(negativPos);
                        simulation::optTracing(lstComp, lstPhoton);
                        prev = calcSum();

                        funcCalls++;
                        funcCalls++;

                        double gradient = (post - prev) / (2 * step);

                        double alpha = 1;
                        double roh = 0.5;
                        double sigma = 0.005;
                        int counterNew = 0;

                        std::vector<double> next = newPos + ((alpha * (-1) * gradient) * diff);

                        static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(next);
                        simulation::optTracing(lstComp, lstPhoton);
                        newSum1 = calcSum();
                        funcCalls++;

                        newSum2 = curRes + (alpha * sigma * (gradient*gradient*(-1)));
                        while (newSum1 > newSum2) {
                            alpha = alpha * roh;
                            next = newPos + ((alpha * (-1) * gradient) * diff);

                            static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(next);
                            simulation::optTracing(lstComp, lstPhoton);
                            newSum1 = calcSum();
                            funcCalls++;
                            newSum2 = curRes + (alpha * sigma * (gradient * (-1) * gradient));
                            counterNew++;
                        }
                        double oldRes = curRes;
                        newPos = newPos + (alpha * gradient * (-1)) * diff;

                        static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(newPos);
                        simulation::optTracing(lstComp, lstPhoton);
                        newRes = calcSum();
                        funcCalls++;

                        difference = pow((oldRes - newRes), 2);
                        difference = sqrt(difference);
                        curMin = newRes;
                        std::cout<<curMin<<std::endl;
                        absCur = absCur+(alpha * gradient * (-1));
                    }

                }
                std::cout<<"Im done with the Focus-Opt"<<std::endl;
                break;
            case lensOneSided:
            if(true){
                //Zuerst Detektor auf Brennweite setzen als vorkond.
                std::vector<double> diff = (lstComp->elem(i+1)->getPosition())-(lstComp->elem(i-1)->getPosition());
                double abs = Utils::getAbs(diff);
                Utils::normalizeVector(diff);
                double d = static_cast<LensTwoSided&>(*lstComp->elem(i)).getD();
                abs = abs - d;
                std::vector<double> newPos(3);


                double step=abs/50;
                double prev, post, newRes, difference = 200;
                double newSum1;
                double newSum2;
                std::vector<double> positivePos(3);
                std::vector<double> negativPos(3);
                double curRes;
                double funcCalls=0;
                double curMini = 1000000;
                std::vector<double> curMinVec(3);
                std::vector<double> cur = lstComp->elem(i-1)->getPosition();
                double absCur;


                for(int j=0; j<50; j++){
                    std::vector<double> next = cur + (step*j)*diff;
                    static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(next);
                    simulation::optTracing(lstComp, lstPhoton);
                    double q = calcSum();
                    std::cout<<q<<std::endl;
                    if(q<curMini){
                        absCur = (step*j);
                        curMini = q;
                        curMinVec = next;
                    }
                }
                newPos = curMinVec;
                lstComp->elem(i)->setPosition(newPos);

                while (difference > 0.0001 && absCur>0) {
                    //Berechne Gradienten
                    simulation::optTracing(lstComp, lstPhoton);
                    curRes = calcSum();
                    funcCalls++;
                    positivePos = newPos + step*diff;
                    negativPos = newPos - step*diff;

                    static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(positivePos);
                    simulation::optTracing(lstComp, lstPhoton);
                    post = calcSum();

                    static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(negativPos);
                    simulation::optTracing(lstComp, lstPhoton);
                    prev = calcSum();

                    funcCalls++;
                    funcCalls++;

                    double gradient = (post - prev) / (2 * step);

                    double alpha = 1;
                    double roh = 0.5;
                    double sigma = 0.005;
                    int counterNew = 0;

                    std::vector<double> next = newPos + ((alpha * (-1) * gradient) * diff);

                    static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(next);
                    simulation::optTracing(lstComp, lstPhoton);
                    newSum1 = calcSum();
                    funcCalls++;

                    newSum2 = curRes + (alpha * sigma * (gradient*gradient*(-1)));
                    while (newSum1 > newSum2) {
                        alpha = alpha * roh;
                        next = newPos + ((alpha * (-1) * gradient) * diff);

                        static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(next);
                        simulation::optTracing(lstComp, lstPhoton);
                        newSum1 = calcSum();
                        funcCalls++;
                        newSum2 = curRes + (alpha * sigma * (gradient * (-1) * gradient));
                        counterNew++;
                    }
                    double oldRes = curRes;
                    newPos = newPos + (alpha * gradient * (-1)) * diff;

                    static_cast<LensTwoSided&>(*lstComp->elem(i)).setPosition(newPos);
                    simulation::optTracing(lstComp, lstPhoton);
                    newRes = calcSum();
                    funcCalls++;

                    difference = pow((oldRes - newRes), 2);
                    difference = sqrt(difference);
                    curMin = newRes;
                    std::cout<<curMin<<std::endl;
                    absCur = absCur+(alpha * gradient * (-1));
                }

            }
            std::cout<<"Im done with the Focus-Opt"<<std::endl;
            break;
        }

    }
}

double Optim::startOptim(){
    std::cout<<"Vor der Opti: "<<calcSum()<<std::endl;
    OAimprove();
    //Reihenfolge festlegen
    if(weightB>weightF){
        optBright();
        optFocus();
    }else{
        optFocus();
        optBright();
    }
    std::cout<<"Nach der Opti: "<<calcSum()<<std::endl;
    return curMin;
}


double Optim::calcSum() {
    Detector _detect = static_cast<Detector&>(*lstComp->elem(lstComp->getLength()-1));
    _detect.createImage();
    double focus = _detect.getSharpness();
    double bright = _detect.getBrightness();
    double sum = focus*weightF + bright*weightB;
    return sum;
}


Optim::Optim(short& _bright, short& _focus, short& _doF, List* _lstComp, std::vector<Photon>* _photList, Config::object* _object,double _fLastLens) {
    lstPhoton = _photList;
    object = _object;
    lstComp = _lstComp;
    std::vector<double> _origin(3);
    _origin[0]=128;
    _origin[1]=128;
    _origin[2]=0;
    origin = _origin;
    weightB = _bright;
    weightF = _focus;
    maxPhot = lstPhoton->size();
    fLastLens = _fLastLens;
}
