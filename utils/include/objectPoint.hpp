#pragma once


class objectPoint{
private:
    const int wavelength;
    const std::vector<double> postion;
public:
    const int& getWavelength();
    const std::vector<double>& getPosition();
    objectPoint(std::vector<double>&, int&);
};
