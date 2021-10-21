#include "mainRoutine.hpp"

#include "../../utils/include/utils.hpp"

namespace simulation {

    void startTracing(Config::object &_object, int maxAnzPhot, List* lstComp, std::vector<Photon> &lstPhotonHit, QProgressBar* _prog) {
        PhotonGenerator photonGenerator(_object);
        for (int i = 0; i < maxAnzPhot; i++) {
            Photon p = photonGenerator.generatePhoton();
            Photon pSafe = p;
            std::vector<double> curDir = lstComp->elem(0)->getPosition();
            Utils::normalizeVector(curDir);
            bool isActive = true;
            for (int i = 0; i < lstComp->getLength(); i++) {
                ComponentType className = lstComp->elem(i)->getType();
                switch (className) {
                    case filter:
                        if(!static_cast<Filter &>(*lstComp->elem(i)).getOutDir(p)) isActive=false;
                        break;
                    case lensOneSided:
                        if(static_cast<LensOneSided &>(*lstComp->elem(i)).getOutDir(p))isActive=false;
                        break;
                    case lensTwoSided:
                        if(static_cast<LensTwoSided &>(*lstComp->elem(i)).getOutDir(p))isActive=false;
                        break;
                    case mirrorElliptical:
                        if(static_cast<MirrorElliptical &>(*lstComp->elem(i)).getOutDir(p, curDir))isActive=false;
                        break;
                    case mirrorCircle:
                        if(static_cast<MirrorCircle &>(*lstComp->elem(i)).getOutDir(p, curDir))isActive=false;
                        break;
                    case mirrorRectangle:
                        if(static_cast<MirrorRectangle &>(*lstComp->elem(i)).getOutDir(p, curDir))isActive=false;
                        break;
                    case mirrorSquare:
                        if(static_cast<MirrorSquare &>(*lstComp->elem(i)).getOutDir(p, curDir))isActive=false;
                        break;
                    case detector:
                        static_cast<Detector &>(*lstComp->elem(i)).getInPoint(p);
                        lstPhotonHit.push_back(pSafe);
                        break;
                    default:
                        break;
                }
                if (i < lstComp->getLength() - 1) {
                    curDir = lstComp->elem(i + 1)->getPosition() - lstComp->elem(i)->getPosition();
                    Utils::normalizeVector(curDir);
                }
                //Überprüfen ob noch aktiv, sonst Schleife abbrechen
                if(!isActive)i=lstComp->getLength();
            }
            _prog->setValue(i);
        }
    }

    void optTracing(List* lstComp, std::vector<Photon> &lstPhotonHit) {
        static_cast<Detector &>(*lstComp->elem(lstComp->getLength()-1)).createImage();//TODO: Sensor leeren
        int maxAnzPhot = lstPhotonHit.size();
        for (int i = 0; i < maxAnzPhot; i++) {
            Photon p = lstPhotonHit[i];
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

    void doStuff(short _bright,short _focus,short _doF, Config::object &_object, List* lstComp, std::vector<Photon> &lstPhotonHit) {
        //aktuelle Summe berechnen, dann Optimierung starten
        double fLastLens = static_cast<LensTwoSided&>(*lstComp->elem(lstComp->getLength()-2)).getF();
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
