#include <string>
typedef double (*cb_fun)(double);
double find_root(cb_fun fun, cb_fun grad,
		 double p0, double p1, double a, double b,
		 const double toler, const int niter,
		 std::string method);
