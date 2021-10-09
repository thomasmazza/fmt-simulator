#pragma once

#include <boost/numeric/ublas/vector.hpp>

typedef typename boost::numeric::ublas::vector<double> vector;
/*
 * Erster Vektor ist der Ergebnisvektor
 * Zweiter und Dritter Vektor sind die b
 */
void cross_product(vector&, vector&, vector&);

//Normiert Vektoren
void normalize(vector&);


vector cross_product_2(vector&, vector&);


double dot_product(vector&, vector&);