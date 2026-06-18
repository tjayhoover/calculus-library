#include <homework/hw3.h>

#include <calculus/integration.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <climits>
#include <vector>
#include <numbers>

using namespace std;

namespace {

double phi(double x) {
    return (1.0 / sqrt(2.0 * numbers::pi)) * exp(-0.5 * pow(x, 2.0));
}

} // namespace

void run_hw3_problem11() {
    vector<double> t_vals = {0.1, 0.5, 2.0};

    for(double t: t_vals) {
        cout << "===== t = " << defaultfloat << t << " =====" << endl;
        auto integrandA = [t](double u) -> double {
                if (u >= 1.0) {
                    return 0.0; // limiting value as u approaches 1 from below
                }
                return phi(t + (u / (1.0 - u))) * (1.0 / pow(1.0-u, 2.0));
            };


        auto integrandB = [](double x) -> double {return phi(x);};

        double diff = INT_MAX;
        int n = 4;
        double tol = 1e-12;

        double val = integrate_simpsons(0.0, 1.0, n, integrandA);

        cout << "Method A:" << endl;
        cout << setw(12) << "n" << setw(24) << "N(t) approx" << setw(24) << "abs diff" << endl;
        cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val << setw(24) << "-" << endl;

        // Method A approximation
        while(diff > tol) {
            n *= 2;
            double new_val = integrate_simpsons(0.0, 1.0, n, integrandA);
            diff = abs(new_val - val);
            val = new_val;
            cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val
                 << setw(24) << scientific << setprecision(3) << diff << fixed << endl;
        };

        cout << "Final n = " << n << ", N(t) = " << setprecision(12) << val << endl << endl;


        diff = INT_MAX;
        n = 4;
        val = 0.5 - integrate_simpsons(0.0, t, n, integrandB);

        cout << "Method B:" << endl;
        cout << setw(12) << "n" << setw(24) << "N(t) approx" << setw(24) << "abs diff" << endl;
        cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val << setw(24) << "-" << endl;

        // Method B approximation
        while(diff > tol) {
            n *= 2;
            double new_val = 0.5 - integrate_simpsons(0.0, t, n, integrandB);
            diff = abs(new_val - val);
            val = new_val;
            cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val
                 << setw(24) << scientific << setprecision(3) << diff << fixed << endl;
        };

        cout << "Final n = " << n << ", N(t) = " << setprecision(12) << val << endl << endl;
    }
}

void run_hw3_problem12() {
    vector<double> T_vals = {0.5, 1.0, 1.5, 2.0};

    for(double t: T_vals) {
        cout << "===== t = " << defaultfloat << t << " =====" << endl;
        auto integrand = [](double t) -> double {
               return 0.05 / (1.0 + (2.0 * exp(-1.0 * pow(1 + t, 2.0))));
            };

        double diff = INT_MAX;
        int n = 4;
        double tol = 1e-12;

        double val = integrate_simpsons(0.0, t, n, integrand);

        cout << setw(12) << "n" << setw(24) << "integral approx" << setw(24) << "abs diff" << endl;
        cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val << setw(24) << "-" << endl;

        // Rate curve integration approximation
        while(diff > tol) {
            n *= 2;
            double new_val = integrate_simpsons(0.0, t, n, integrand);
            diff = abs(new_val - val);
            val = new_val;
            cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val
                 << setw(24) << scientific << setprecision(3) << diff << fixed << endl;
        };

        double discount = exp(-1.0 * val);
        int discount_places = (t == 2.0) ? 8 : 6;
        cout << "Discount factor D(0," << defaultfloat << t << ") = "
             << fixed << setprecision(discount_places) << discount << endl;

        cout << "Final n = " << n << ", integral = " << setprecision(12) << val << endl << endl;
    }
}

void run_hw3_problem13() {
    auto integrand13 = [](double y) -> double {
        if (y <= 0.0 || y >= 1.0) return 0.0;   // limiting values
        double s = 0.28 * sqrt(0.5); // vol times sqrt(T)
        double d = log(100) + ((0.04 - 0.015 - (0.5 * 0.28 * 0.28)) * 0.5) - log(95);
        double a = sqrt(1 - y) / y;
        double b = exp(-1 * (pow(log(y) + d, 2.0) / (2 * s * s)));
        return a * b;
    };


    cout << "Option value calculator (Q13 ii): " << endl;

    double diff = INT_MAX;
    int n = 8;
    double tol = 1e-8;

    double val = integrate_simpsons(0.0, 1.0, n, integrand13);
    double option_value = 12 * exp(-0.04 * 0.5) * val / (0.28 * sqrt(numbers::pi));

    cout << setw(12) << "n" << setw(24) << "integral approx" << setw(24) << "abs diff" << endl;
    cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val << setw(24) << "-" << endl;

    // Calculate the integral for the payoff
    while(diff > tol) {
        n *= 2;
        double new_val = integrate_simpsons(0.0, 1.0, n, integrand13);
        double new_option_value = 12 * exp(-0.04 * 0.5) * new_val / (0.28 * sqrt(numbers::pi));

        diff = abs(new_option_value - option_value);
        val = new_val;
        option_value = new_option_value;
        cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val
                << setw(24) << scientific << setprecision(3) << diff << fixed << endl;
    };

    cout << "Value of the option: " << defaultfloat << " = "
            << fixed << setprecision(6) << option_value << endl;

    cout << "Final n = " << n << ", integral = " << setprecision(12) << val << endl << endl;

    cout << "Option value calculator (Q13 iii): " << endl;

    // This one is AI generated, got tired of typing them out ;)
    auto integrand13iii = [](double u) -> double {
        if (u <= 0.0 || u >= 1.0) return 0.0;   // limiting values H(0)=H(1)=0

        double S0 = 100.0, K = 95.0, r = 0.04, q = 0.015, sig = 0.28, T = 0.5;
        double mu = log(S0) + (r - q - 0.5*sig*sig)*T;
        double d  = mu - log(K);
        double s2 = sig*sig*T;                  // s^2 = sigma^2 * T

        double one_minus_u2 = 1.0 - u*u;        // = y
        double expo = log(one_minus_u2) + d;    // ln(1-u^2) + d

        return (2.0*u*u / one_minus_u2) * exp(-(expo*expo) / (2.0*s2));
    };

    diff = INT_MAX;
    n = 8;
    tol = 1e-8;

    val = integrate_simpsons(0.0, 1.0, n, integrand13iii);
    option_value = 12 * exp(-0.04 * 0.5) * val / (0.28 * sqrt(numbers::pi));


    cout << setw(12) << "n" << setw(24) << "integral approx" << setw(24) << "abs diff" << endl;
    cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val << setw(24) << "-" << endl;

    // Calculate the integral for the payoff
    while(diff > tol) {
        n *= 2;
        double new_val = integrate_simpsons(0.0, 1.0, n, integrand13iii);
        double new_option_value = 12 * exp(-0.04 * 0.5) * new_val / (0.28 * sqrt(numbers::pi));
        diff = abs(new_option_value - option_value);
        val = new_val;
        option_value = new_option_value;
        cout << setw(12) << n << setw(24) << fixed << setprecision(12) << val
                << setw(24) << scientific << setprecision(3) << diff << fixed << endl;
    };


    cout << "Value of the option: " << defaultfloat << " = "
            << fixed << setprecision(6) << option_value << endl;

    cout << "Final n = " << n << ", integral = " << setprecision(12) << val << endl << endl;
}
