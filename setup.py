import glob
import numpy
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext

files = ['numa.pyx'] + glob.glob('src/*.cpp')
setup(
    name='_numa',
    ext_modules=[Extension('_numa',
                           sources=files, language="c++",
                           include_dirs=[numpy.get_include()])],
    cmdclass={'build_ext': build_ext},
)
