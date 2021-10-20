#pragma once

#include "component.hpp"
#include "../../photon/include/photon.hpp"

class MirrorCircle : public Component{
private:
    double radius;
public:
    MirrorCircle(std::vector<double>&, std::vector<double>&, double);
    std::string getType();
    MirrorCircle(const MirrorCircle& mirrorCircle1);
    bool calcOut(Photon&, std::vector<double>&, std::vector<double>&);
    bool getOutDir(Photon&, std::vector<double>&);
    double getRadius();
    void setRadius(double  _radius);
};
