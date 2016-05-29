from math import *
import numa as na

def test_bisect1():
    def fun(x):
        return 1 - x
    a = na.bisect(fun, -1, 2)
    assert abs(a - 1.) < 1e-6

def test_bisect2():
    def fun1(x):
        return (x + 4.0) * x * x - 10.0
    a = na.bisect(fun1, -1, 2)
    assert abs(a - 1.365229845046997) < 1e-14

def test_fixed_point():
    def fun(x):
        return sqrt(10.0 / (4.0 + x))
    a = na.fixed_point(fun, 3.4)
    assert abs(a - 1.36523013) < 1e-8

def test_newton_raphson():
    def fun(x):
        return cos(x) - x
    def grad(x):
        return -sin(x) - 1.
    a = na.newton_raphson(fun, grad, 1.)
    assert abs(a - 0.739085) < 1e-6

def test_secant_method():
    def fun(x):
        return cos(x) - x
    a = na.secant_method(fun, .5, 1.)
    assert abs(a - 0.739085) < 1e-6

def test_regula_falsi():
    def fun(x):
        return cos(x) - x
    a = na.regula_falsi(fun, .5, 1.)
    assert abs(a - 0.739085) < 1e-6
