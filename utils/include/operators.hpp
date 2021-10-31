#pragma once

#include <vector>
#include <iostream>

std::vector<double> operator+(const std::vector<double>& vector1, const std::vector<double>& vector2);

std::vector<double> operator-(const std::vector<double>& vector1, const std::vector<double>& vector2);

std::vector<double> operator-(const std::vector<double>& _vector);

std::vector<double> operator*(const std::vector<double>& vector1, const double& scalar);

std::vector<double> operator*(const double& scalar, const std::vector<double>& vector1);

std::ostream& operator<<(std::ostream& os,const std::vector<double>& vector1);
