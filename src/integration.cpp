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

double integrate_simpsons(double a, double b, int n, function<double(double)> f_int) {
    double h = (b - a) / n;
    double i_simpson = f_int(a) / 6 + f_int(b) / 6;

    for(int i = 1; i < n; ++i) {
        i_simpson = i_simpson + (f_int(a + (i * h)) / 3);
    }
    for(int i = 1; i <= n; ++i) {
        i_simpson = i_simpson + (2 * (f_int(a + ((i - 0.5) * h))) / 3);
    }
    return i_simpson * h;
}

double compute_with_tolerance(double tol, function<double(int)> compute_approximation) {
    int n = 4;
    double i_old = compute_approximation(n);
    n = 2*n;
    double i_new = compute_approximation(n);
    while(abs(i_new - i_old) > tol) {
        i_old = i_new;
        n = 2*n;
        i_new = compute_approximation(n);
    }
    return i_new;
}
