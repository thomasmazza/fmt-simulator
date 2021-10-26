#pragma once

#include "component.hpp"
#include "../../photon/include/photon.hpp"

class Aperture : public Component{
private:
    double radius;
public:
    Aperture(std::vector<double>&, std::vector<double>&, double);
    std::string getType();
    Aperture(const Aperture& aperture);
    bool getOutDir(Photon&, std::vector<double>&);
    double getRadius();
    void setRadius(double  _radius);
};
