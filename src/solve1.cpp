/*
*   GAUSSIAN ELIMINATION WITH BACKWARD SUBSTITUTION ALGOTITHM
*   Burden and Faires Algorithm 6.1
*
*   To solve the n by n linear system
*
*   E1:  A[1,1] X[1] + A[1,2] X[2] +...+ A[1,n] X[n] = A[1,n+1]
*   E2:  A[2,1] X[1] + A[2,2] X[2] +...+ A[2,n] X[n] = A[2,n+1]
*   :
*   .
*   EN:  A[n,1] X[1] + A[n,2] X[2] +...+ A[n,n] X[n] = A[n,n+1]
*
*/

#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "solve1.h"

using namespace std;

#define ZERO 1.0E-20

vector<double> solve1(vector<vector<double> > &A, vector<double> &b,
		      string const method="backward")
{

  string method_l = method;
  transform(method_l.begin(), method_l.end(), method_l.begin(), ::tolower);

  if (method_l == "backward") {
    return solve_backward_sub(A, b);
  }

  string message = "Unrecognized method: " + method;
  throw runtime_error(message);
}

vector<double> solve_backward_sub(vector<vector<double> > &A, vector<double> &b)
{
  int i, ip, j, jj, k, m, n, nn;
  int ichg=0;
  double c, xm, sum;
  bool OK=true;

  n = A.size();
  vector<double> x(n);

  /* Append b to A */
  for (i=0; i<n; i++){
    A[i].push_back(b[i]);
  }

  i = 1;
  nn = n - 1;
  m = n + 1;
  while ((OK) && (i<=nn)) {
    /* Use ip instead of p */
    ip = i;
    while ((fabs(A[ip-1][i-1]) <= ZERO) && (ip <= n)) {
      ip++;
    }

    if (ip == m) {
      OK = false;
    } else {
      if (ip != i) {
	for (jj=1; jj<=m; jj++) {
	  c = A[i-1][jj-1];
	  A[i-1][jj-1] = A[ip-1][jj-1];
	  A[ip-1][jj-1] = c;
	}
	ichg += 1;
      }

      jj = i + 1;
      for (j=jj; j<=n; j++) {
	/* use XM in place of m(j,i) */
	xm = A[j-1][i-1] / A[i-1][i-1];
	for (k=jj; k<=m; k++) {
	  A[j-1][k-1] = A[j-1][k-1] - xm * A[i-1][k-1];
	}
	/*  Multiplier XM could be saved in A[j,i].  */
	A[j-1][i-1] = 0.0;
      }
    }
    i += 1;
  }

  if (!OK || (fabs(A[n-1][n-1]) <= ZERO)) {
    string message = "System has no unique solution";
    throw runtime_error(message);
  }

  /* start backward substitution */
  x[n-1] = A[n-1][m-1] / A[n-1][n-1];

  for (k=1; k<=nn; k++) {
    i = nn - k + 1;
    jj = i + 1;
    sum = 0.0;
    for (int kk=jj ; kk<=n; kk++) {
      sum = sum - A[i-1][kk-1] * x[kk-1];
    }
    x[i-1] = (A[i-1][m-1] + sum) / A[i-1][i-1];
  }

  return x;
}
