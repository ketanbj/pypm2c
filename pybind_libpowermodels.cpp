#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <iostream>

#include "libpowermodelscompiled.h" // Include the header file

namespace py = pybind11;

// Define a function to wrap `c_solve_power_flow` and convert the result to a Python string
std::string solve_power_flow_wrapper(const std::string& path) {
    char* result = c_solve_power_flow(const_cast<char*>(path.c_str()));
    if (!result) {
        throw std::runtime_error("c_solve_power_flow returned NULL");
    }
    std::string output(result);
    free(result); // Ensure memory cleanup
    return output;
}

int py_load_grid(const std::string& path) {
    std::cout << "Loading grid from " << path << std::endl;

    int status  = c_load_grid("case5.m");
    return status;
}

// Pybind11 module definition
PYBIND11_MODULE(pypm2c, m) {
    m.doc() = "Python bindings for libpowermodelscompiled"; // Module docstring

    m.def("increment32", &increment32, "Increment a 32-bit integer");
    m.def("increment64", &increment64, "Increment a 64-bit integer");
    m.def("c_load_grid", &py_load_grid, "Load grid from a given file path");

    // Wrap `c_solve_power_flow` to return a Python string
    m.def("c_solve_power_flow", &solve_power_flow_wrapper, "Solve power flow and return JSON result");
}