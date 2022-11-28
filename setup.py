import os
import glob
import shutil
from setuptools import setup
from setuptools.command.install import install
from distutils.sysconfig import get_python_lib


__library_file__ = './lib/pypowerboard*.so'
__version__ = "0.0.1"
__author__ = "LMWafer"


#-[] Utility class to install bindings
class CopyLibFile(install):
    """"
    Directly copy library file to python's site-packages directory.
    """
    def run(self):
        install_dirs = get_python_lib()
        print(install_dirs)
        lib_file = glob.glob(__library_file__)
        assert len(lib_file) == 1 and len(install_dirs) >= 1     

        print(f"copying {lib_file[0]} -> {install_dirs[0]}")
        shutil.copy(lib_file[0], install_dirs)


setup(
    name = "pypowerboard",
    version = __version__,
    description = "A python binding for powerboard I2C driver.",
    author = __author__,
    keywords = "binding i2c powerboard driver motor controler",
    url = "https://github.com/LMWafer/powerboard-driver",
    long_description = open('README.md').read(),
    author_email = "louismarie.restout@gmail.com",
    cmdclass=dict(
        install=CopyLibFile
    ),
    classifiers =[
        "Topic :: System :: Hardware :: Hardware Drivers",
        "Programming Language :: Python :: 3",
        "Programming Language :: C++",
        "Operating System :: Unix",
        "Natural Language :: English",
        "License :: OSI Approved :: MIT License",
        "Development Status :: 3 - Alpha"
    ],
    license="MIT"
)
