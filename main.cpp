#include <iostream>
#include <calculus/integration.h>

using namespace std;

int main(int, char**){
   
    cout << "Hello, from calculus-library!" << endl;

    std::function<double(double)> f = [](double a) -> double {return a*a;};

    cout << integrate_midpoint(0.0, 1.0, 10, f) << endl;
    cout << integrate_trapezoid(0.0, 1.0, 10, f) << endl;
}
