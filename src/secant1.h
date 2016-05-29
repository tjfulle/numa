typedef double (*cb_fun)(double);
double secant_method(cb_fun fun, double p0, double p1,
		     const double toler, const int niter);
