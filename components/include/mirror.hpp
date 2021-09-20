#pragma once
#include <boost/numeric/ublas/vector.hpp>
#include "component.hpp"
typedef typename boost::numeric::ublas::vector<double> vector;

class Mirror: public Component {
    private:
    //Habe jetzt erstmal die Ebene als drei Punkte dargestellt. Muss dies nicht auch in Components?
        vector plane[3];
    public:
        //Muss die Methode nicht in Component? und benötigt diese nicht einen Photon anstatt eines Vectors?
        bool hitComponent(vector);
        //Kann diese Methode nicht auch ein Photon bekommen?
        vector getOutDir(vector&, vector&);

        Mirror(vector&, vector&, vector&, vector&, vector&);
};



