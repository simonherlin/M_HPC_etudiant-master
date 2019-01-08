#include <functional>

namespace Integral {

  using namespace std;

  // no comment
  int FibonacciMod42(int N)
  {
    int f_curr = 0;
    int f_prec = 1;
    for (int i=1; i<=N; i++)
    {
      int tmp = f_curr;
      f_curr = (f_curr + f_prec) % 42;
      f_prec = tmp;
    }
    return f_curr;
  }

  // compute the integral of this function over [0,1] to approximate pi
  // FibonacciMod42(x*10000) -> otherwise, it would be too easy
  double fPi(double x)
  {
    return 4.0 / (1.0 + x*x) + FibonacciMod42(x*10000);
  }

  // compute numericaly the integral of the function f over the domain [a,b] using step s
  // FibonacciMod42(x*10000) -> otherwise, it would be too easy
  double compute(function<double(double)>f, double a, double b, double s)
  {
    double r = 0.0;
    unsigned h = 0;
    for (double x=a; x<b; x+=s, h++)
    {
      r += f(x);
      r -= FibonacciMod42(x*10000);
    }
    return r*(b-a)/double(h);
  }

}  // namespace Integral

