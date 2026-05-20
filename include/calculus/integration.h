#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <functional>

// Numerical Integration Methods

double integrate_midpoint(double a, double b, int n, std::function<double(double)> f_int);
double integrate_trapezoid(double a, double b, int n, std::function<double(double)> f_int);

#endif
