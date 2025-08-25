#!/usr/bin/env python3
"""
Setup script for FinCraftr - A bilingual quantitative finance toolkit.

This setup script uses pybind11 to build C++ extensions for Python.
"""

import os
import sys
import subprocess
from pathlib import Path

from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir
import pybind11
from setuptools import setup, Extension

# Read the contents of README file
this_directory = Path(__file__).parent
long_description = (this_directory / "README.md").read_text()

# Define the extension module using standard pybind11 extension
ext_modules = [
    Pybind11Extension(
        "fincraftr.pyfincraftr",
        sources=[
            "python/bindings/main.cpp",
        ],
        include_dirs=[
            "cpp/include",
            pybind11.get_cmake_dir() + "/../include",
        ],
        language="c++",
        cxx_std=20,
    ),
]

setup(
    name="fincraftr",
    version="1.0.0",
    author="FinCraftr Contributors",
    author_email="",
    description="FinCraftr - A bilingual quantitative finance toolkit",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/danielyekini/fincraftr",
    project_urls={
        "Bug Tracker": "https://github.com/danielyekini/fincraftr/issues",
        "Documentation": "https://github.com/danielyekini/fincraftr#readme",
    },
    classifiers=[
        "Development Status :: 4 - Beta",
        "Intended Audience :: Financial and Insurance Industry",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
        "Programming Language :: C++",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Programming Language :: Python :: 3.12",
        "Topic :: Office/Business :: Financial",
        "Topic :: Scientific/Engineering :: Mathematics",
    ],
    package_dir={"": "python"},
    packages=["fincraftr", "fincraftr.equity", "fincraftr.options", "fincraftr.rates", "fincraftr.forwards"],
    python_requires=">=3.8",
    install_requires=[
        "numpy>=1.19.0",
    ],
    extras_require={
        "dev": [
            "pytest>=6.0",
            "pytest-cov",
            "black",
            "isort",
            "flake8",
        ],
        "docs": [
            "sphinx",
            "sphinx-rtd-theme",
            "myst-parser",
        ],
    },
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    include_package_data=True,
)
