#include <iostream>
#include <cmath>
#include <calculus/integration.h>
#include <bonds/bond_pricing.h>
#include <options/black_scholes.h>
#include <homework/hw3.h>
#include <iomanip>
#include <climits>

using namespace std;

int main(int, char**){
   
    cout << "Hello, from calculus-library!" << endl;

    // function<double(double)> f = [](double a) -> double {return a*a;};

    // cout << integrate_midpoint(0.0, 1.0, 10, f) << endl;
    // cout << integrate_trapezoid(0.0, 1.0, 10, f) << endl;

    // function<double(double)> f_std = [](double a) -> double {return exp(-a * a);};

    // cout << "Testing tolerance code: " << endl;
    // cout << setprecision(8) << compute_with_tolerance(1e-7, [f_std](int n) -> double {return integrate_midpoint(0.0, 2.0, n, f_std);}) << endl;

    // vector<double> t_cash_flow = {1, 2, 3};
    // vector<double> v_cash_flow = {10.0, 10.0, 20.0};
    // auto r_zero = [](int t) -> double { return 0.05;};

    // cout << "Bond pricing: " << endl;
    // cout << bond_price_r0(3, t_cash_flow, v_cash_flow, r_zero) << endl;

    // vector<double> tol = {1e-6, 1e-6, 1e-6};

    // cout << bond_price_ri(3, t_cash_flow, v_cash_flow, r_zero, tol) << endl;

    // double yield = 0.065;
    // vector<double> v_cash_flow2 = {3.0, 3.0, 3.0, 103.0};
    // vector<double> t_cash_flow2 = {2.0/12.0, 8.0/12.0, 14.0/12.0, 20.0/12.0};
    // tuple<double, double, double> bond_price_and_derivs = bond_price_with_derivatives(4, t_cash_flow2, v_cash_flow2, yield);
    
    // cout << "Bond price given yield: " << get<0>(bond_price_and_derivs) << endl;
    // cout << "Bond duration: " << get<1>(bond_price_and_derivs) << endl;
    // cout << "Bond convexity: " << get<2>(bond_price_and_derivs) << endl;
    

    // pair<double, double> option_prices = black_scholes(0, 50, 45, 0.5, 0.2, 0.06, 0.02);
    // cout << "Call price: " << option_prices.first << endl;
    // cout << "Put price: " << option_prices.second << endl;
    // cout << "Exercise 2.3" << endl;


    // auto sqrt_x = [](double x) -> double {return sqrt(x);};
    // auto f2 = [](double x) -> double {return (pow(x, 2.5) / (1 + pow(x, 2)));};

    run_hw3_problem11();
    run_hw3_problem12();
    run_hw3_problem13();
}