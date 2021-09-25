#pragma once

#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;
/*
 * Erster Vektor ist der Ergebnisvektor
 * Zweiter und Dritter Vektor sind die b
 */
void cross_product(vector&, vector&, vector&);