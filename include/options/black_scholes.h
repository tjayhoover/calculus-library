#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

#include <utility>

double cum_dist_normal(double t);

// Returns the Black-Scholes price of a European call and put option with these
// parameters. The call price is the first in the pair; the put is the second.
std::pair<double, double> black_scholes(double t, double S, double K, double T, double vol, double r, double q);

#endif
