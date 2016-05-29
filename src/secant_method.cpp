/*
*   SECANT ALGORITHM, Burden-Faires Algorithm 2.4
*
*   To find a solution to the equation f(x) = 0
*   given initial approximations p0 and p1:
*
*/

#include <cmath>
#include <stdexcept>
#include <string>

#include "secant_method.h"

using namespace std;
typedef double (*cb_fun)(double);

double secant_method(cb_fun fun, double p0, double p1,
		     const double toler, const int niter) {

  double f0, f1, p, fp;
  f0 = (*fun)(p0);
  f1 = (*fun)(p1);
  for (int i=0; i<niter; i++) {
    /* Compute P(I) */
    p = p1 - f1 * (p1 - p0) / (f1 - f0);
    fp = (*fun)(p);
    if (fabs(p - p1) < toler) {
      return p;
    }
    p0 = p1;
    f0 = f1;
    p1 = p;
    f1 = fp;
  }
  /* Root not found */
  string message = "secant_method failed to converge";
  throw runtime_error(message);
}
