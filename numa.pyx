#
# Wrapper for the Bisection algortihm
#
cdef object py_bisect_fun
cdef extern from "src/bisect.h":
    double bisect(double (*fun)(double), double A, double B,
                  const double toler, const int niter)
def _bisect(fun, A, B, double toler=1e-6, int niter=1000):
    global py_bisect_fun
    py_bisect_fun = fun
    return bisect(c_bisect_cb, A, B, toler, niter)
cdef double c_bisect_cb(double x):
    return (<object>py_bisect_fun)(x)

#
# Wrapper for the Fixed Point algortihm
#
cdef object py_fixedpt_fun
cdef extern from "src/fixpt1.h":
    double fixed_point(double (*fun)(double), double p0,
                       const double toler, const int niter)
def _fixed_point(fun, p0, double toler=1e-6, int niter=1000):
    global py_fixedpt_fun
    py_fixedpt_fun = fun
    return fixed_point(c_fixedpt_cb, p0, toler, niter)
cdef double c_fixedpt_cb(double x):
    return (<object>py_fixedpt_fun)(x)

#
# Wrapper for the Newton-Raphson algortihm
#
cdef object py_newtraph_fun
cdef object py_newtraph_grad
cdef extern from "src/newton1.h":
    double newton_raphson(double (*fun)(double), double (*grad)(double),
                          double p0, const double toler, const int niter)
def _newton_raphson(fun, grad, p0, double toler=1e-6, int niter=1000):
    global py_newtraph_fun
    global py_newtraph_grad
    py_newtraph_fun = fun
    py_newtraph_grad = grad
    return newton_raphson(c_newtraph_fun_cb, c_newtraph_grad_cb, p0, toler, niter)
cdef double c_newtraph_fun_cb(double x):
    return (<object>py_newtraph_fun)(x)
cdef double c_newtraph_grad_cb(double x):
    return (<object>py_newtraph_grad)(x)

#
# Wrapper for the Secant Method algortihm
#
cdef object py_secant_fun
cdef extern from "src/secant1.h":
    double secant_method(double (*fun)(double), double p0, double p1,
                         const double toler, const int niter)
def _secant_method(fun, p0, p1, double toler=1e-6, int niter=1000):
    global py_secant_fun
    py_secant_fun = fun
    return secant_method(c_secant_cb, p0, p1, toler, niter)
cdef double c_secant_cb(double x):
    return (<object>py_secant_fun)(x)

#
# Wrapper for the Regula Falsi Method algortihm
#
cdef object py_regulafalsi_fun
cdef extern from "src/regula_falsi.h":
    double regula_falsi(double (*fun)(double), double p0, double p1,
                        const double toler, const int niter)
def _regula_falsi(fun, p0, p1, double toler=1e-6, int niter=1000):
    global py_regulafalsi_fun
    py_regulafalsi_fun = fun
    return regula_falsi(c_regulafalsi_cb, p0, p1, toler, niter)
cdef double c_regulafalsi_cb(double x):
    return (<object>py_regulafalsi_fun)(x)
