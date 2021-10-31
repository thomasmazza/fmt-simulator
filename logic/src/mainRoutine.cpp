#include "mainRoutine.hpp"
#include "../../utils/include/utils.hpp"

namespace simulation {

/**
 * @brief startTracing is the main routine for the ray tracing
 * @param _object, object file for generating new photons
 * @param maxAnzPhot, maximum no. of photons that should be emitted
 * @param _lstComp, is the component list for tracing
 * @param _prog, is the progressbar of the GUI
 * @return std::vector<Photon>*, the list of photons that hit the detektor
 *
 * This code is parallelized with OpenMP with one shared object, the setupList, which is necessary due to the accesses from every core.
 * The progressbar and the detector got an Omp-Critical flag due to their special tasks in the tracing which depends on precison.
 */
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
                    case aperture:
                        isActive = static_cast<Aperture &>(*lstComp->elem(j)).getOutDir(p, curDir);
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

    /**
     * @brief startTracing2 is the a copy from the main routine for the ray tracing but without the progressbar
     * @param _object, object file for generating new photons
     * @param maxAnzPhot, maximum no. of photons that should be emitted
     * @param _lstComp, is the component list for tracing
     * @return std::vector<Photon>*, the list of photons that hit the detektor
     *
     * This code is parallelized with OpenMP with one shared object, the setupList, which is necessary due to the accesses from every core.
     * The progressbar and the detector got an Omp-Critical flag due to their special tasks in the tracing which depends on precison.
     */
    std::vector<Photon>* startTracing2(Config::object &_object, int maxAnzPhot, List* lstComp){
        static_cast<Detector &>(*lstComp->elem(lstComp->getLength()-1)).resetSensor();
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
                    case aperture:
                        isActive = static_cast<Aperture &>(*lstComp->elem(j)).getOutDir(p, curDir);
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
        }
        return photonLst;
    }

    /**
     * @brief optTracing is the main routine for the optimizer to trace the photons that hit again and again
     * @param _lstComp, is the component list for tracing
     * @param lstPhotonHit, list of photons that hit the detector in the first tracing
     * @return number of photons that hit the detektor
     *
     * This code is parallelized with OpenMP with one shared object, the setupList, which is necessary due to the accesses from every core.
     * The detector got an Omp-Critical flag due to its special tasks in the tracing which depends on precison.
     */

    int optTracing(List* lstComp, std::vector<Photon>* lstPhotonHit) {
        static_cast<Detector &>(*lstComp->elem(lstComp->getLength()-1)).resetSensor();
        int maxAnzPhot = lstPhotonHit->size();
        int hit=0;
        #pragma omp parallel for shared (lstComp, hit)
        for (int i = 0; i < maxAnzPhot; i++) {
            Photon p = lstPhotonHit->at(i);
            std::vector<double> origin(3);
            origin[0]=128;
            origin[1]=128;
            origin[2]=0;
            std::vector<double> curDir = lstComp->elem(0)->getPosition();
            curDir = curDir - origin;
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
                    case aperture:
                        static_cast<Aperture &>(*lstComp->elem(i)).getOutDir(p, curDir);
                        break;
                    case detector:
                        #pragma omp critical
                        static_cast<Detector &>(*lstComp->elem(i)).getInPoint(p);
                        #pragma omp critical
                        hit++;
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
        return hit;
    }

    /**
     * @brief doStuff starts the Optimizer
     * @param _bright, sets weight of brightness in the sum
     * @param _focus, sets weight of focus in the sum
     * @param _doF, sets weight of doF in the sum
     * @param _object, object file for generating new photons
     * @param _lstComp, is the component list for tracing
     * @param lstPhotonHit, is the list of photons that hit the detector
     */
    void doStuff(short _bright,short _focus,short _doF, Config::object &_object, List* lstComp, std::vector<Photon>* lstPhotonHit) {
        //aktuelle Summe berechnen, dann Optimierung starten
        double fLastLens;
        double diff;
        std::vector<double> dif(3);
        //Zuerst Letzte Linse (Doppelseitig) finden und den Abstand berechnen + Brennweite letzte Linsen berechnen
        std::cout<<lstPhotonHit->size()<<std::endl;
        for(int i=lstComp->getLength()-1; i>=0; i--){
            ComponentType className = lstComp->elem(i)->getType();
            switch (className) {
                case lensTwoSided:
                    fLastLens = static_cast<LensTwoSided&>(*lstComp->elem(i)).getF();
                    dif = lstComp->elem(i)->getPosition() - lstComp->elem(i+1)->getPosition();
                    diff += Utils::getAbs(dif);
                    i=-1;
                    break;
                default:
                    if(i<lstComp->getLength()-1 && i>1){
                        dif = lstComp->elem(i)->getPosition() - lstComp->elem(i-1)->getPosition();
                        diff += Utils::getAbs(dif);
                    }
                    break;
            }
        }
        Detector _detect = static_cast<Detector &>(*lstComp->elem(lstComp->getLength()-1));
        _detect.createImage();
        Config::object* objectPointer = new Config::object(_object);
        Optim opt(_bright, _focus, _doF, lstComp, lstPhotonHit, objectPointer, fLastLens);
        double newSum = opt.startOptim();
    }

    /**
     * @brief getDof calculates the DoF for the GUI(intended to be part of optimization)
     * @param _lstComp, is the component list for tracing
     */
    double getDof(List* lstComp){
        double fLastLens;
        double diff;
        std::vector<double> dif(3);
        //Zuerst Letzte Linse (Doppelseitig) finden und den Abstand berechnen + Brennweite letzte Linsen berechnen
        for(int i=lstComp->getLength()-1; i>=0; i--){
            ComponentType className = lstComp->elem(i)->getType();
            switch (className) {
                case lensTwoSided:
                    fLastLens = static_cast<LensTwoSided&>(*lstComp->elem(i)).getF();
                    dif = lstComp->elem(i)->getPosition() - lstComp->elem(i+1)->getPosition();
                    diff += Utils::getAbs(dif);
                    i=-1;
                    break;
                default:
                    if(i<lstComp->getLength()-1 && i>1){
                        dif = lstComp->elem(i)->getPosition() - lstComp->elem(i-1)->getPosition();
                        diff += Utils::getAbs(dif);
                    }
                    break;
            }
        }
        return Utils::depthOfField(fLastLens, diff);
    }
}
