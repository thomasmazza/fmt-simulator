#pragma once

class RGB {
public:
    double r;
    double g;
    double b;
    double intensity;
    void setRGB(double &, double &, double &);
    RGB();
    RGB(double &, double &, double &, double &);
    RGB(double, double, double, double);
    RGB(const RGB&); //Kopierkonstruktor
};


