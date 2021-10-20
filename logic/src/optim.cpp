#include "../include/optim.hpp"

void Optim::OAimprove(){

    //TODO: Optimierung über versetzen der Komponenten auf die optische Achse mit Abstand von davor (Problem mit den Listen)
    std::vector<double> curDir = lstComp->elem(0)->getPosition();
    Utils::normalizeVector(curDir);
    Photon phot1(origin, curDir, 600);
    for(int i = 1; i<lstComp->getLength()-1; i++) {
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
        nextPos = phot1.getPosition() + abs*phot1.getDirection();
        lstComp->elem(i)->setPosition(nextPos);
        curDir = nextPos - curPos;
        Utils::normalizeVector(curDir);
    }
    //TODO: Simulieren und auf besserung hoffen ;D
}

void Optim::optBright(){
    //TODO: Optimerung über Filter, Grenzen anpassen bis zu einem gewissen Level
}

void Optim::optFocus(){
    //TODO: Optimierung über einen BP und Abstand von ankommenden Photonen auf dem Detektor
    double focus = static_cast<Detector&>(*lstComp->elem(lstComp->getLength()-1)).getPixelSize();//TODO: getFocus
    for(int i=lstComp->getLength()-1; i>=0; i--){
        ComponentType className = lstComp->elem(i)->getType();
        switch (className) {
            case lensTwoSided:
                if((lstComp->getLength()-i) < 3){
                    //Zuerst Detektor auf Brennweite setzen als vorkond.
                    std::vector<double> diff = (lstComp->elem(i+1)->getPosition())-(lstComp->elem(i)->getPosition());
                    double abs = Utils::getAbs(diff);
                    Utils::normalizeVector(diff);
                    double f = static_cast<LensTwoSided&>(*lstComp->elem(i)).getN();
                    std::vector<double> newPos(3);
                    newPos = (lstComp->elem(i)->getPosition()) + f*diff;
                    lstComp->elem(i+1)->setPosition(newPos);

                    double step=abs/100;
                    double prev, post, newRes, difference = 200;
                    double newSum1;
                    double newSum2;
                    std::vector<double> positivePos(3);
                    std::vector<double> negativPos(3);
                    double curRes;
                    double funcCalls=0;

                    while (difference > 0.2) {
                        //Berechne Gradienten
                        //TODO:: Simulieren
                        curRes = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus
                        funcCalls++;
                        positivePos = newPos + step*diff;
                        negativPos = newPos - step*diff;

                        static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(positivePos);
                        //TODO:: Simulieren
                        post = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus

                        static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(negativPos);
                        //TODO:: Simulieren
                        prev = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus

                        funcCalls++;
                        funcCalls++;

                        double gradient = (post - prev) / (2 * step);

                        double alpha = 100;
                        double roh = 0.9;
                        double sigma = 0.5;
                        int counterNew = 0;

                        std::vector<double> next = newPos + ((alpha * (-1) * gradient) * diff);

                        static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(next);
                        //TODO:: Simulieren
                        newSum1 = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus
                        funcCalls++;

                        newSum2 = curRes + (alpha * sigma * (gradient*gradient*(-1)));
                        //std::cout<<"Pre"<<std::endl;
                        while (newSum1 > newSum2) {
                            alpha = alpha * roh;
                            next = newPos + ((alpha * (-1) * gradient) * diff);

                            static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(next);
                            //TODO:: Simulieren
                            newSum1 = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus
                            funcCalls++;
                            newSum2 = curRes + (alpha * sigma * (gradient * (-1) * gradient));
                            counterNew++;
                            std::cout<<counterNew<<std::endl;
                        }
                        double oldRes = curRes;
                        newPos = newPos + (alpha * gradient * (-1)) * diff;

                        static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(newPos);
                        //TODO:: Simulieren
                        newRes = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus
                        funcCalls++;

                        difference = pow((oldRes - newRes), 2);
                        difference = sqrt(difference);
                    }

                }
                break;
            case lensOneSided:
                if((lstComp->getLength()-i) < 3){
                    //Zuerst Detektor auf Brennweite setzen als vorkond.
                    std::vector<double> diff = (lstComp->elem(i+1)->getPosition())-(lstComp->elem(i)->getPosition());
                    double abs = Utils::getAbs(diff);
                    Utils::normalizeVector(diff);
                    double f = static_cast<LensOneSided&>(*lstComp->elem(i)).getN();
                    std::vector<double> newPos(3);
                    newPos = (lstComp->elem(i)->getPosition()) + f*diff;
                    lstComp->elem(i+1)->setPosition(newPos);

                    double step=abs/100;
                    double prev, post, newRes, difference = 200;
                    double newSum1;
                    double newSum2;
                    std::vector<double> positivePos(3);
                    std::vector<double> negativPos(3);
                    double curRes;
                    double funcCalls=0;

                    while (difference > 0.2) {
                        //Berechne Gradienten
                        //TODO:: Simulieren
                        curRes = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus
                        funcCalls++;
                        positivePos = newPos + step*diff;
                        negativPos = newPos - step*diff;

                        static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(positivePos);
                        //TODO:: Simulieren
                        post = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus

                        static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(negativPos);
                        //TODO:: Simulieren
                        prev = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus

                        funcCalls++;
                        funcCalls++;

                        double gradient = (post - prev) / (2 * step);

                        double alpha = 100;
                        double roh = 0.9;
                        double sigma = 0.5;
                        int counterNew = 0;

                        std::vector<double> next = newPos + ((alpha * (-1) * gradient) * diff);

                        static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(next);
                        //TODO:: Simulieren
                        newSum1 = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus
                        funcCalls++;

                        newSum2 = curRes + (alpha * sigma * (gradient*gradient*(-1)));
                        //std::cout<<"Pre"<<std::endl;
                        while (newSum1 > newSum2) {
                            alpha = alpha * roh;
                            next = newPos + ((alpha * (-1) * gradient) * diff);

                            static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(next);
                            //TODO:: Simulieren
                            newSum1 = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus
                            funcCalls++;
                            newSum2 = curRes + (alpha * sigma * (gradient * (-1) * gradient));
                            counterNew++;
                            std::cout<<counterNew<<std::endl;
                        }
                        double oldRes = curRes;
                        newPos = newPos + (alpha * gradient * (-1)) * diff;

                        static_cast<Detector&>(*lstComp->elem(i+1)).setPosition(newPos);
                        //TODO:: Simulieren
                        newRes = static_cast<Detector&>(*lstComp->elem(i+1)).getPixelSize(); //TODO:getFocus
                        funcCalls++;

                        difference = pow((oldRes - newRes), 2);
                        difference = sqrt(difference);
                    }

                }
                break;
            default:
                break;
        }

    }
    double newFocus = static_cast<Detector&>(*lstComp->elem(lstComp->getLength()-1)).getPixelSize(); //TODO: getFocus()
    focus = focus - newFocus;
    std::cout<<"Improved by : "<<focus<<", the new Sum is: "<<calcSum()<<std::endl;
}

void Optim::optDoF(){
    //TODO: Optimierung über Abstand Linse Detektor
}

void Optim::startOptim(){
    OAimprove();
    //Reihenfolge festlegen
    if(weightB>weightDoF){
        if(weightB>weightF){
            if(weightDoF>weightF){
                optBright();
                optDoF();
                optFocus();
            }else{
                optBright();
                optFocus();
                optDoF();
            }
        }else{
            optFocus();
            optBright();
            optDoF();
        }
    }else{
        if(weightB>weightF){
            optDoF();
            optBright();
            optFocus();

        }else{
            if(weightDoF>weightF){
                optDoF();
                optFocus();
                optBright();
            }else{
                optFocus();
                optDoF();
                optBright();
            }
        }
    }
    double newMin = calcSum();
    std::cout<<"Improved by: "<<startSum-newMin<<std::endl;
    startSum = newMin;
}

double Optim::calcSum() {
    double focus = static_cast<Detector&>(*lstComp->elem(lstComp->getLength()-1)).getPixelSize(); //TODO: getFocus()
    double bright = static_cast<Detector&>(*lstComp->elem(lstComp->getLength()-1)).getPixelSize(); //TODO: getBright()
    double DoF = static_cast<Detector&>(*lstComp->elem(lstComp->getLength()-1)).getPixelSize(); //TODO: getdoF
    double sum = focus*weightF + bright*weightB + DoF*weightDoF;
    return sum;
}

Optim::Optim(short& _bright, short& _focus, short& _doF, double& _startSum,List* _lstComp, std::vector<Photon>& _photList) {
    for(int i=0; i<_photList.size(); i++){
        lstPhoton.push_back(_photList[i]);
    }
    lstComp = _lstComp;
    std::vector<double> _origin(3);
    _origin[0]=0;
    _origin[1]=0;
    _origin[2]=0;
    origin = _origin;
    weightB = _bright;
    weightF = _focus;
    weightDoF = _doF;
    startSum = _startSum;
    startOptim();
}
