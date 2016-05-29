/*
*   BISECTION ALGORITHM
*
*   To find a solution to f(x) = 0 given the continuous function
*   f on the interval [a,b], where f(a) and f(b) have
*   opposite signs:
*
*/

double bisect1(double (*f)(double), double A, double B,
	       double toler, int niter);
