/*
*   BISECTION ALGORITHM
*
*   To find a solution to f(x) = 0 given the continuous function
*   f on the interval [a,b], where f(a) and f(b) have
*   opposite signs:
*
*/
typedef double (*cb_fun)(double);
double bisect(cb_fun fun, double A, double B, const double toler, const int niter);
