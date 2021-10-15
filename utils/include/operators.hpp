#pragma once

#include <vector>

std::vector<double> operator+(const std::vector<double>& vector1, const std::vector<double>& vector2);

std::vector<double> operator-(const std::vector<double>& vector1, const std::vector<double>& vector2);

std::vector<double> operator*(const std::vector<double>& vector1, const double& scalar);

std::vector<double> operator*(const double& scalar, const std::vector<double>& vector1);