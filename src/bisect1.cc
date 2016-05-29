/*
*   BISECTION ALGORITHM 2.1
*
*   To find a solution to f(x) = 0 given the continuous function
*   f on the interval [a,b], where f(a) and f(b) have
*   opposite signs:
*
*/

#include <cmath>
#include <stdexcept>
#include <string>
#include "bisect1.h"

using namespace std;

double bisect1(double (*f)(double), double A, double B,
               const double toler, const int niter)
{

  double P, FA, FB, C, FP;

  if (A > B) {
    double tmp;
    tmp = A;
    A = B;
    B = tmp;
  }

  if (A - B + 1. == 1.) {
    string message = "A cannot equal B";
    throw runtime_error(message);
  }

  FA = (*f)(A);
  FB = (*f)(B);
  if (FA * FB > 0.0) {
    string message = "Root not bracketed";
    throw runtime_error(message);
  }

  for (int i=0; i<=niter; i++) {
    C = (B - A) / 2.0;
    P = A + C;
    FP = (*f)(P);
    if ((fabs(FP) < 1.e-20) || (C < toler)) {
      /* Procedure completed successfully */
      return P;
    }

    /* Compute A(i) and B(i) */
    if ((FA * FP) > 0.0) {
      A = P; FA = FP;
    }
    else {
      B = P; FB = FP;
    }
  }

  /* Root not found */
  string message = "bisection failed to converge";
  throw runtime_error(message);

}
