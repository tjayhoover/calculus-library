#include <bonds/bond_pricing.h>
#include <calculus/integration.h>

#include <vector>
#include <functional>
#include <cmath>

using namespace std;

double bond_price_r0(int n, vector<double> t_cash_flow, vector<double> v_cash_flow, 
                    function<double(double)> r_zero) {
                    double price = 0.0;
                    for(int i = 0; i < n; ++i) {
                        double discount_i = exp(-1*t_cash_flow[i]*r_zero(t_cash_flow[i]));
                        price += (v_cash_flow[i] * discount_i);
                    }
                    return price;
                  }

double bond_price_ri(int n, vector<double> t_cash_flow, vector<double> v_cash_flow, 
                    function<double(double)> r_inst, vector<double> tol) {
                    double price = 0.0;

                    for(int i = 0; i < n; ++i) {
                      double r = compute_with_tolerance(tol[i], [&t_cash_flow, i, &r_inst](int n) -> double {return integrate_simpsons(0.0, t_cash_flow[i], n, r_inst);});
                      double disc = exp(-1*r); // don't need to multiply by t here; we never multiplied integral by 1/t
                      price = price + (v_cash_flow[i] * disc);
                    }
                    return price;
}

tuple<double, double, double> bond_price_with_derivatives(int n, vector<double> t_cash_flow, vector<double> v_cash_flow, double yield) {
  double price = 0.0;
  double duration = 0.0;
  double convexity = 0.0;

  for(int i = 0; i < n; ++i) {
    double disc = exp(-1 * t_cash_flow[i] * yield);
    price += v_cash_flow[i] * disc;
    duration += t_cash_flow[i] * v_cash_flow[i] * disc;
    convexity += pow(t_cash_flow[i], 2) * v_cash_flow[i] * disc;
  }

  return {price, duration/price, convexity/price};
}