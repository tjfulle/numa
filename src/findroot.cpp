#include <cmath>
#include <string>
#include <stdexcept>

#include "findroot.h"
#include "bisect.h"
#include "newton1.h"
#include "secant1.h"
#include "fixpt1.h"
#include "regula_falsi.h"

using namespace std;
typedef double (*cb_fun)(double);

double find_root(cb_fun fun, cb_fun grad=NULL,
		 double p0=0., double p1=0., double a=0., double b=0.,
		 const double toler=1e-6, const int niter=25,
		 string method="newton")
{
  string method_l = method;
  transform(method_l.begin(), method_l.end(), method_l.begin(), ::tolower);

  if (method_l == "bisect") {
    return bisect(fun, a, b, toler, niter);
  }
  else if (method_l == "newton") {
    return newton_raphson(fun, grad, p0, toler, niter);
  }
  else if (method_l == "secant") {
    return secant_method(fun, p0, p1, toler, niter);
  }
  else if (method_l == "fixed_point") {
    return fixed_point(fun, p0, toler, niter);
  }
  else if (method_l == "regula_falsi") {
    return regula_falsi(fun, p0, p1, toler, niter);
  }

  string message = "Unrecognized root finding method: " + method;
  throw runtime_error(message);
}
