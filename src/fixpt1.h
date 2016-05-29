typedef double (*cb_fun)(double);
double fixed_point(cb_fun fun, double p0, const double toler, const int niter);
