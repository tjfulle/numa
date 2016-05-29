import glob
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext

files = ['numa.pyx'] + glob.glob('src/*.cpp')
setup(
    name='_numa',
    ext_modules=[Extension('_numa', sources=files, language="c++")],
    cmdclass={'build_ext': build_ext}
)
