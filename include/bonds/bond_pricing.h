#ifndef BOND_PRICING_H
#define BOND_PRICING_H

#include <vector>
#include <functional>
#include <tuple>

// Returns the price of a bond given its cash flows and a function which returns the zero rate at time t
double bond_price_r0(int n, std::vector<double> t_cash_flow, std::vector<double> v_cash_flow, 
    std::function<double(double)> r_zero);

// Returns the price of a bond given its cash flows and a function which returns the instantaneous interest rate at time t
double bond_price_ri(int n, std::vector<double> t_cash_flow, std::vector<double> v_cash_flow, 
    std::function<double(double)> r_inst, std::vector<double> tol);

// Returns a tuple containing the price, duration, and convexity (in that order) of a bond given its cash flows and yield
std::tuple<double, double, double> bond_price_with_derivatives(int n, std::vector<double> t_cash_flow,
    std::vector<double> v_cash_flow, double yield);

#endif
