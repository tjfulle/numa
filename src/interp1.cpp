#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>

#include "interp1.h"

using namespace std;

double interp1(double const x, vector<double> &xp, vector<double> &fp)
{
  return neville(x, xp, fp);
}

double neville(double const x, vector<double> &xp, vector<double> &fp)
{
  /*
   *   NEVILLE'S ITERATED INTERPOLATION ALGORITHM 3.1
   *
   *   To evaluate the interpolating polynomial P on the
   *   (n+1) distinct numbers x(0), ..., x(n) at the number x
   *   for the function f:
   *
  */
  int n = xp.size();
  int i, j;
  double top, bot;
  vector<double> q = fp;
  if (xp.size() != fp.size()) {
    string message = "fp and xp are not of the same length";
    throw runtime_error(message);
  }

  if (x <= xp[0]) {
    return fp[0];
  } else if (x >= xp[n-1]) {
    return fp[n-1];
  }

  q = fp;
  for (j=1; j<n; j++) {
    for (i=n-1; i>(j-1); i--) {
      top = ((x - xp[i-j]) * q[i]) - ((x - xp[i]) * q[i-1]);
      bot = xp[i] - xp[i-j];
      q[i] = top / bot;
    }
  }
  return q[n-1];
}
