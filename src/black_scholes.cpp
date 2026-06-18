#include <options/black_scholes.h>

#include <numbers>
#include <cmath>
#include <utility>

using namespace std;

double cum_dist_normal(double t) {
    double z = abs(t);
    double y = 1 / (1 + 0.2316419 * z);
    double a1 = 0.319381530;
    double a2 = -0.356563782;
    double a3 = 1.781477937;
    double a4 = -1.821255978;
    double a5 = 1.330274429;

    double m = 1-exp(-1*(pow(t,2)) / 2)*(a1*y+a2*pow(y,2)+a3*pow(y,3)
                +a4*pow(y,4)+a5*pow(y,5))/sqrt(2*numbers::pi);

    if(t > 0) return m;
    else return (1 - m);
}

pair<double, double> black_scholes(double t, double S, double K, double T, double vol, double r, double q) {
    double d1 = (log(S / K) + (r - q + (pow(vol, 2) / 2.0)) * (T - t)) / (vol * sqrt(T - t));
    double d2 = d1 - (vol * sqrt(T - t));
    double C = (S*exp(-1 * q * (T - t)) * cum_dist_normal(d1)) - (K * exp(-1 * r * (T - t)) * cum_dist_normal(d2));
    double P = (K*exp(-1 * r * (T - t)) * cum_dist_normal(-1 * d2)) - (S * exp(-1 * q * (T - t)) * cum_dist_normal(-1 * d1));
    return {C, P};
}
