import numa as na

def test_bisect():
    def fun(x):
        return 1 - x
    a = na.bisect(fun, -1, 2)
    assert abs(a - 1.) < 1e-6

    def fun1(x):
        return (x + 4.0) * x * x - 10.0
    a = na.bisect(fun1, -1, 2)
    assert abs(a - 1.365229845046997) < 1e-14
