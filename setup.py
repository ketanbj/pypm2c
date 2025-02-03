from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "pypm2c",
        ["pybind_libpowermodels.cpp"],
        include_dirs=[pybind11.get_include(), "pm2c/PowerModelsCompiled/include"],
        libraries=["powermodelscompiled", "julia"],
        library_dirs=["pm2c/PowerModelsCompiled/lib", "pm2c/PowerModelsCompiled/lib/julia"],
        extra_compile_args=["-std=c++11"],
    )
]

setup(
    name="pypm2c",
    version="0.1",
    ext_modules=ext_modules,
    zip_safe=False,
)