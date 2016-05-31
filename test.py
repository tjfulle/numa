from math import *
import pytest
import numpy as np
import numa as na

def test_bisect0():
    def fun(x):
        return 1 - x
    a = na.bisect(fun, -1, 2)
    assert abs(a - 1.) < 1e-6
    b = na.find_root(fun, a=-1, b=2, method='bisect')
    assert abs(a - b) < 1e-12

def test_bisect1():
    def fun(x):
        return 1 - x
    a = na.bisect(fun, -1, 2)
    assert abs(a - 1.) < 1e-6

def test_bisect2():
    def fun(x):
        return (x + 4.0) * x * x - 10.0
    a = na.bisect(fun, -1, 2)
    assert abs(a - 1.365229845046997) < 1e-14
    b = na.find_root(fun, a=-1, b=2, method='bisect')
    assert abs(a - b) < 1e-12

def test_bisect_not_bracketed():
    def fun(x):
        return x ** 2 - 1.
    with pytest.raises(RuntimeError):
        # Root not bracketed - see if exception is raised
        a = na.bisect(fun, 2., 4.)

def test_fixed_point():
    def fun(x):
        return sqrt(10.0 / (4.0 + x))
    a = na.fixed_point(fun, 3.4)
    assert abs(a - 1.36523013) < 1e-8
    b = na.find_root(fun, p0=3.4, method='fixed_point')
    assert abs(a - b) < 1e-12

def test_newton_raphson():
    def fun(x):
        return cos(x) - x
    def grad(x):
        return -sin(x) - 1.
    a = na.newton_raphson(fun, grad, 1.)
    assert abs(a - 0.739085) < 1e-6
    b = na.find_root(fun, grad=grad, p0=1, method='newton')
    assert abs(a - b) < 1e-12

def test_secant_method():
    def fun(x):
        return cos(x) - x
    a = na.secant_method(fun, .5, 1.)
    assert abs(a - 0.739085) < 1e-6
    b = na.find_root(fun, p0=.5, p1=1., method='secant')
    assert abs(a - b) < 1e-12

def test_regula_falsi():
    def fun(x):
        return cos(x) - x
    a = na.regula_falsi(fun, .5, 1.)
    assert abs(a - 0.739085) < 1e-6
    b = na.find_root(fun, p0=.5, p1=1., method='regula_falsi')
    assert abs(a - b) < 1e-12

def test_solve1():
    A = np.array([[1., 0.], [0., 2.]])
    b = np.array([2, 4])
    x = na.solve1(A, b)
    assert np.allclose(x, [2, 2])

def test_solve1_error():
    A = np.array([[1., 0.], [0., 0.]])
    b = np.array([2, 4])
    with pytest.raises(RuntimeError):
        x = na.solve1(A, b)

def test_solve1_2():
    A = np.array([[1.0, -1.0,  2.0, -1.0],
                  [2.0, -2.0,  3.0, -3.0],
                  [1.0,  1.0,  1.0,  0.0],
                  [1.0, -1.0,  4.0,  3.0]])
    b = np.array([-8.0, -20.0, -2.0, 4.0])
    x1 = na.solve1(A, b)
    x2 = np.linalg.solve(A, b)
    b2 = np.dot(A, x1)
    assert np.allclose(b, b2)
    assert np.allclose(x1, x2)

def test_interp():
    xp = np.array([0., 1., 2., 3.,  4.])
    fp = np.array([0., 3., 6., 9., 12.])
    for x in (-1., 2., 3.5, 5.5):
        y = na.interp1(x, xp, fp)
        assert abs(y - np.interp(x, xp, fp)) < 1e-12
