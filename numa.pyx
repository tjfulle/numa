import numpy as np
cimport numpy as np
from libcpp.vector cimport vector
from libcpp.string cimport string

# ----------------------------------------------------------------------------- #
# Wrapper for the root finding family of algorithms
# ----------------------------------------------------------------------------- #
cdef object py_findroot_fun
cdef object py_findroot_grad
cdef extern from "src/findroot.h":
    double find_root(double (*fun)(double), double (*grad)(double),
                     double p0, double p1, double a, double b,
                     const double toler, const int niter,
                     string method) except +
def _find_root(fun, grad=None, p0=0., p1=0., a=0., b=0., toler=1e-6,
               niter=1000, method="newton"):
    global py_findroot_fun
    global py_findroot_grad
    py_findroot_fun = fun
    py_findroot_grad = grad
    return find_root(c_findroot_fun_cb, c_findroot_grad_cb, p0, p1,
                     a, b, toler, niter, method.encode("UTF-8"))
cdef double c_findroot_fun_cb(double x):
    return (<object>py_findroot_fun)(x)
cdef double c_findroot_grad_cb(double x):
    return (<object>py_findroot_grad)(x)

# ----------------------------------------------------------------------------- #
# Wrapper for the Bisection algortihm
# ----------------------------------------------------------------------------- #
cdef object py_bisect_fun
cdef extern from "src/bisect.h":
    double bisect(double (*fun)(double), double A, double B,
                  const double toler, const int niter) except +
def _bisect(fun, A, B, double toler=1e-6, int niter=1000):
    global py_bisect_fun
    py_bisect_fun = fun
    return bisect(c_bisect_cb, A, B, toler, niter)
cdef double c_bisect_cb(double x):
    return (<object>py_bisect_fun)(x)

# ----------------------------------------------------------------------------- #
# Wrapper for the Fixed Point algortihm
# ----------------------------------------------------------------------------- #
cdef object py_fixedpt_fun
cdef extern from "src/fixpt1.h":
    double fixed_point(double (*fun)(double), double p0,
                       const double toler, const int niter) except +
def _fixed_point(fun, p0, double toler=1e-6, int niter=1000):
    global py_fixedpt_fun
    py_fixedpt_fun = fun
    return fixed_point(c_fixedpt_cb, p0, toler, niter)
cdef double c_fixedpt_cb(double x):
    return (<object>py_fixedpt_fun)(x)

# ----------------------------------------------------------------------------- #
# Wrapper for the Newton-Raphson algortihm
# ----------------------------------------------------------------------------- #
cdef object py_newtraph_fun
cdef object py_newtraph_grad
cdef extern from "src/newton1.h":
    double newton_raphson(double (*fun)(double), double (*grad)(double),
                          double p0, const double toler, const int niter) except +
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

# ----------------------------------------------------------------------------- #
# Wrapper for the Secant Method algortihm
# ----------------------------------------------------------------------------- #
cdef object py_secant_fun
cdef extern from "src/secant1.h":
    double secant_method(double (*fun)(double), double p0, double p1,
                         const double toler, const int niter) except +
def _secant_method(fun, p0, p1, double toler=1e-6, int niter=1000):
    global py_secant_fun
    py_secant_fun = fun
    return secant_method(c_secant_cb, p0, p1, toler, niter)
cdef double c_secant_cb(double x):
    return (<object>py_secant_fun)(x)

# ----------------------------------------------------------------------------- #
# Wrapper for the Regula Falsi Method algortihm
# ----------------------------------------------------------------------------- #
cdef object py_regulafalsi_fun
cdef extern from "src/regula_falsi.h":
    double regula_falsi(double (*fun)(double), double p0, double p1,
                        const double toler, const int niter) except +
def _regula_falsi(fun, p0, p1, double toler=1e-6, int niter=1000):
    global py_regulafalsi_fun
    py_regulafalsi_fun = fun
    return regula_falsi(c_regulafalsi_cb, p0, p1, toler, niter)
cdef double c_regulafalsi_cb(double x):
    return (<object>py_regulafalsi_fun)(x)

# ----------------------------------------------------------------------------- #
# Wrapper for the solve algortihm
# ----------------------------------------------------------------------------- #
cdef extern from "src/solve1.h":
    vector[double] solve1(vector[vector[double]] &A,
                          vector[double] &x,
                          string method) except +
def _solve1(A1, b1, method="backward"):
    cdef np.ndarray[double, mode='c', ndim=2] A
    cdef np.ndarray[double, mode='c'] b
    A = np.ascontiguousarray(A1, dtype=float)
    b = np.ascontiguousarray(b1, dtype=float)
    return np.array(solve1(A, b, method.encode("UTF-8")))

# ----------------------------------------------------------------------------- #
# Wrapper for the Neville interpolation algortihm
# ----------------------------------------------------------------------------- #
cdef extern from "src/interp1.h":
    double interp1(double x, vector[double] &xp, vector[double] &fp) except +
def _interp1(x, xp, fp):
    cdef np.ndarray[double, mode='c'] xp_
    cdef np.ndarray[double, mode='c'] fp_
    xp_ = np.ascontiguousarray(xp, dtype=float)
    fp_ = np.ascontiguousarray(fp, dtype=float)
    return interp1(x, xp_, fp_)
