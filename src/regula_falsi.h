typedef double (*cb_fun)(double);
double regula_falsi(cb_fun fun, double p0, double p1,
		    const double toler, const int niter);
