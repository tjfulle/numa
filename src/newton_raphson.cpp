/*
*   NEWTON-RAPHSON ALGORITHM, Burden-Faires Algorithm 2.3
*
*   To find a solution to f(x) = 0 given an
*   initial approximation p0:
*
*/

#include <cmath>
#include <stdexcept>
#include <string>

#include "newton_raphson.h"

using namespace std;
typedef double (*cb_fun)(double);

double newton_raphson(cb_fun fun, cb_fun grad,
		      double p0, const double toler, const int niter) {
  double D, f, g;

  f = (*fun)(p0);

  for (int i=0; i<niter; i++) {
    g = (*grad)(p0);
    D = f / g;
    p0 -= D;
    f = (*fun)(p0);
    if (fabs(D) < toler) {
      return p0;
    }
  }

  /* Root not found */
  string message = "newton_raphson failed to converge";
  throw runtime_error(message);
}
