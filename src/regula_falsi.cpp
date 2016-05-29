/*
*   METHOD OF FALSE POSITION ALGORITHM, Burden-Faires Algorithm 2.5
*
*   To find a solution to f(x) = 0 given the continuous function
*   f on the interval [p0,p1], where f(p0) and f(p1) have
*   opposite signs:
*
*/

#include <cmath>
#include <stdexcept>
#include <string>

#include "regula_falsi.h"

using namespace std;
typedef double (*cb_fun)(double);

double regula_falsi(cb_fun fun, double p0, double p1,
		    const double toler, const int niter) {

  double q, q0, q1, p;

  q0 = (*fun)(p0);
  q1 = (*fun)(p1);

  if (q0 * q1 > 0.0) {
    string message = "Root not bracketed";
    throw runtime_error(message);
  }

  for (int i=0; i<niter; i++) {
    /* Compute P(I) */
    p = p1 - q1 * (p1 - p0) / (q1 - q0);
    q = (*fun)(p);
    if (fabs(p - p1) < toler) {
      /* Procedure completed successfully */
      return p;
    }
    /* Compute P0(I) and P1(I) */
    if ((q * q1) < 0.0) {
      p0 = p1; q0 = q1;
    }
    p1 = p; q1 = q;
  }
  /* Root not found */
  string message = "regula_falsi failed to converge";
  throw runtime_error(message);
}
