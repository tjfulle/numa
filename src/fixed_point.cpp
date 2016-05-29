/*
* FIXED-POINT ALGORITHM, Burden-Faires Algorithm 2.2
*
* To find a solution to p = g(p) given an
* initial approximation p0
*
*/

#include <cmath>
#include <stdexcept>
#include <string>

#include "fixed_point.h"

using namespace std;
typedef double (*cb_fun)(double);

double fixed_point(cb_fun fun, double p0, const double toler, const int niter) {
  double p;
  for (int i=0; i<niter; i++) {
    p = (*fun)(p0);
    if (fabs(p - p0) < toler) {
      return p;
    }
    p0 = p;
  }
  /* Fixed point not found */
  string message = "fixed_point failed to converge";
  throw runtime_error(message);
}
