# python setup module for n_tree

from distutils.core import setup
from distutils.extension import Extension

setup(name="PackageName",
    ext_modules=[
        Extension("n_tree", ["ntreemodule.cpp"],
        libraries = ["boost_python"])
    ])