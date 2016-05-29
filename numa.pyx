#
# Wrapper for the bisection algortihm
#
cdef object py_bisect_fun
cdef extern from "src/bisect1.h":
    double bisect1(double (*f)(double), double A, double B, double TOL, int niter)
def bisect(fun, A, B, double toler=1e-6, int niter=1000):
    global py_bisect_fun
    py_bisect_fun = fun
    return bisect1(c_bisect_cb, A, B, toler, niter)
cdef double c_bisect_cb(double x):
    return (<object>py_bisect_fun)(x)
