#include "mirror.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;

Mirror::Mirror(vector& _pos, vector& _normal):Mirror::Component(_pos, _normal){
    //TODO: Nothing
}
