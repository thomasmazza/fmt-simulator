#include "../include/optim.hpp"

void Optim::OAimprove(){
    //TODO: Optimierung über versetzen der Komponenten auf die optische Achse mit Abstand von davor (Problem mit den Listen)
    std::vector<double> curDir = lstComp.elem(0)->getPosition();
    Utils::normalizeVector(curDir);
    Photon phot1(origin, curDir, 600);
    for(int i = 1; i<lstComp.getLength()-1; i++) {
        ComponentType className = lstComp.elem(i-1)->getType();
        switch (className) {
            case filter:
                static_cast<Filter&>(*lstComp.elem(i-1)).getOutDir(phot1);
                break;
            case lensOneSided:
                static_cast<LensOneSided&>(*lstComp.elem(i-1)).getOutDir(phot1);
                break;
            case lensTwoSided:
                static_cast<LensTwoSided&>(*lstComp.elem(i-1)).getOutDir(phot1);
                break;
            case mirrorElliptical:
                static_cast<MirrorElliptical&>(*lstComp.elem(i-1)).getOutDir(phot1, curDir);
                break;
            case mirrorCircle:
                static_cast<MirrorCircle&>(*lstComp.elem(i-1)).getOutDir(phot1, curDir);
                break;
            case mirrorRectangle:
                static_cast<MirrorRectangle&>(*lstComp.elem(i-1)).getOutDir(phot1, curDir);
                break;
            case mirrorSquare:
                static_cast<MirrorSquare&>(*lstComp.elem(i-1)).getOutDir(phot1, curDir);
                break;
            case detector:
                static_cast<Detector&>(*lstComp.elem(i-1)).getInPoint(phot1);
                break;
            default:
                break;
        }
        std::vector<double> curPos =  lstComp.elem(i-1)->getPosition();
        std::vector<double> nextPos = lstComp.elem(i)->getPosition();
        std::vector<double> diff = nextPos - curPos;
        double abs = Utils::getAbs(diff);
        //std::vector<double> trace =
        nextPos = phot1.getPosition() + abs*phot1.getDirection();
        lstComp.elem(i)->setPosition(nextPos);
        curDir = nextPos - curPos;
        Utils::normalizeVector(curDir);
    }
    //Main::makeSim()
}

void Optim::optBright(){
    //TODO: Optimerung über Filter, Grenzen anpassen bis zu einem gewissen Level
}

void Optim::optFocus(){
    //TODO: Optimierung über einen BP und Abstand von ankommenden Photonen auf dem Detektor
    std::vector<Photon> lstPhotParax(1000);
}

void Optim::optDoF(){
    //TODO: Optimierung über Abstand Linse Detektor
}

void Optim::startOptim(){
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


}

Optim::Optim(short& _bright, short& _focus, short& _DoF, double& _startSum, List& _compList, std::vector<Photon>& _photList) {
    lstPhoton = _photList;
    lstComp = _compList;
    std::vector<double> _origin(3);
    _origin[0]=0;
    _origin[1]=0;
    _origin[2]=0;
    origin = _origin;
    weightB = _bright;
    weightF = _focus;
    weightDoF = _DoF;
    startSum = _startSum;
    startOptim();
}

