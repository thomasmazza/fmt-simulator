#include "mainRoutine.hpp"
#include "../../utils/include/utils.hpp"

namespace simulation {

    std::vector<Photon>* startTracing(Config::object &_object, int maxAnzPhot, List* lstComp, QProgressBar* _prog){
        PhotonGenerator photonGenerator(_object);
        std::vector<Photon>* photonLst = new std::vector<Photon>();
        #pragma omp parallel for shared (lstComp)
        for(int i = 0; i < maxAnzPhot; i++){
            Photon p = photonGenerator.generatePhoton();
            Photon pTemp = p;
            std::vector<double> origin(3);
            origin[0]=128;
            origin[1]=128;
            origin[2]=0;
            std::vector<double> curDir = lstComp->elem(0)->getPosition();
            curDir = curDir - origin;
            Utils::normalizeVector(curDir);
            bool isActive = true;
            for(int j = 0; j < lstComp->getLength(); j++){
                ComponentType className = lstComp->elem(j)->getType();
                switch (className) {
                    case filter:
                        isActive = static_cast<Filter &>(*lstComp->elem(j)).getOutDir(p);
                        break;
                    case lensOneSided:
                        isActive = static_cast<LensOneSided &>(*lstComp->elem(j)).getOutDir(p);
                        break;
                    case lensTwoSided:
                        isActive = static_cast<LensTwoSided &>(*lstComp->elem(j)).getOutDir(p);
                        break;
                    case mirrorElliptical:
                        isActive = static_cast<MirrorElliptical &>(*lstComp->elem(j)).getOutDir(p, curDir);
                        break;
                    case mirrorCircle:
                        isActive = static_cast<MirrorCircle &>(*lstComp->elem(j)).getOutDir(p, curDir);
                        break;
                    case mirrorRectangle:
                        isActive = static_cast<MirrorRectangle &>(*lstComp->elem(j)).getOutDir(p, curDir);
                        break;
                    case mirrorSquare:
                        isActive = static_cast<MirrorSquare &>(*lstComp->elem(j)).getOutDir(p, curDir);
                        break;
                    case detector:
                        #pragma omp critical
                        static_cast<Detector &>(*lstComp->elem(j)).getInPoint(p);
                        #pragma omp critical
                        photonLst->push_back(pTemp);
                        break;
                    default:
                        break;
                }
                if(j < lstComp->getLength() - 1){
                    curDir = lstComp->elem(j + 1)->getPosition() - lstComp->elem(j)->getPosition();
                    Utils::normalizeVector(curDir);
                }
                if(!isActive) break;
            }
            #pragma omp critical
            _prog->setValue(_prog->value() + 1);
        }
        return photonLst;
    }

    void optTracing(List* lstComp, std::vector<Photon>* lstPhotonHit) {
        static_cast<Detector &>(*lstComp->elem(lstComp->getLength()-1)).resetSensor();
        int maxAnzPhot = lstPhotonHit->size();
        for (int i = 0; i < maxAnzPhot; i++) {
            Photon p = lstPhotonHit->at(i);
            std::vector<double> curDir = lstComp->elem(0)->getPosition();
            Utils::normalizeVector(curDir);
            for (int i = 0; i < lstComp->getLength(); i++) {
                ComponentType className = lstComp->elem(i)->getType();
                switch (className) {
                    case filter:
                        static_cast<Filter &>(*lstComp->elem(i)).getOutDir(p);
                        break;
                    case lensOneSided:
                        static_cast<LensOneSided &>(*lstComp->elem(i)).getOutDir(p);
                        break;
                    case lensTwoSided:
                        static_cast<LensTwoSided &>(*lstComp->elem(i)).getOutDir(p);
                        break;
                    case mirrorElliptical:
                        static_cast<MirrorElliptical &>(*lstComp->elem(i)).getOutDir(p, curDir);
                        break;
                    case mirrorCircle:
                        static_cast<MirrorCircle &>(*lstComp->elem(i)).getOutDir(p, curDir);
                        break;
                    case mirrorRectangle:
                        static_cast<MirrorRectangle &>(*lstComp->elem(i)).getOutDir(p, curDir);
                        break;
                    case mirrorSquare:
                        static_cast<MirrorSquare &>(*lstComp->elem(i)).getOutDir(p, curDir);
                        break;
                    case detector:
                        static_cast<Detector &>(*lstComp->elem(i)).getInPoint(p);
                        break;
                    default:
                        break;
                }
                if (i < lstComp->getLength() - 1) {
                    curDir = lstComp->elem(i + 1)->getPosition() - lstComp->elem(i)->getPosition();
                    Utils::normalizeVector(curDir);
                }
            }
        }
    }

    void doStuff(short _bright,short _focus,short _doF, Config::object &_object, List* lstComp, std::vector<Photon>* lstPhotonHit) {
        //aktuelle Summe berechnen, dann Optimierung starten
        double fLastLens = static_cast<LensTwoSided&>(*lstComp->elem(lstComp->getLength()-2)).getN(); //TODO: getF()
        std::vector<double> dif = lstComp->elem(lstComp->getLength()-2)->getPosition() - lstComp->elem(lstComp->getLength()-1)->getPosition();
        double absLastLensDet = Utils::getAbs(dif);
        double focus = static_cast<Detector&>(*lstComp->elem(lstComp->getLength()-1)).getSharpness();
        double bright = static_cast<Detector&>(*lstComp->elem(lstComp->getLength()-1)).getBrightness();
        double DoF = Utils::depthOfField(fLastLens, absLastLensDet);
        DoF = (1/DoF);
        double sum = focus*_focus + bright*_bright + DoF*_doF;
        std::cout<<"Sum before Opt: "<<sum<<std::endl;
        Config::object* objectPointer = new Config::object(_object);
        Optim opt(_bright, _focus, _doF, lstComp, lstPhotonHit, objectPointer);
        opt.startOptim();
        sum = focus*_focus + bright*_bright + DoF*_doF;
        std::cout<<"Sum after Opt: "<<sum<<std::endl;

    }
}
