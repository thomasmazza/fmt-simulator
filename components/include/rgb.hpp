#pragma once

class RGB {
public:
    double r;
    double g;
    double b;
    double intensity;
    void setRGB(double &, double &, double &);
    void addRGB(RGB&);
    RGB();
    RGB(double &, double &, double &, double &);
    RGB(double, double, double, double);
    RGB(const RGB&); //Kopierkonstruktor

};


