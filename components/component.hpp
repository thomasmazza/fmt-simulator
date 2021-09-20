//
// Created by Lasse Alsmeyer on 18.09.21.
//

#include <boost/numeric/ublas/vector.hpp>

using namespace boost::numeric::ublas;

namespace component {

    template<typename T>
    class Component {
    private:
        vector<T> pos;
        vector<T> normal;
    public:
        Component(vector<T>&,vector<T>&);
        vector<T>& getPos();
        void setPos(vector<T>&);
        vector<T>& getNormal();
        void setNormal(vector<T>&);
    };
}

#include "src/component.cpp"
