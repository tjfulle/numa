typedef double (*cb_fun)(double);
double newton_raphson(cb_fun fun, cb_fun grad,
		      double p0, const double toler, const int niter);
