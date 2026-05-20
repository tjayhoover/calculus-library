#include <calculus/integration.h>

#include <string>
#include <iostream>
#include <functional>

using namespace std;

double integrate_midpoint(double a, double b, int n, function<double(double)> f_int) {
    double h = (b - a) / n;
    double i_midpoint = 0.0;

    for(int i = 1; i <= n; ++i) {
        i_midpoint = i_midpoint + f_int(a + ((i - 0.5) * h));
    }
    return h * i_midpoint;
}

double integrate_trapezoid(double a, double b, int n, function<double(double)> f_int) {
    double h = (b - a) / n;
    double i_trap = (f_int(a) / 2) + (f_int(b) / 2);

    for(int i = 1; i <= n - 1; ++i) {
        i_trap = i_trap + f_int(a + (i*h));
    }
    return h * i_trap;
}