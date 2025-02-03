#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <iostream>

extern "C"
{
#include "libpowermodelscompiled.h" // Include the header file
#include "julia_init.h"
}
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

int c_load_grid_wrapper(char* path) {
    if (path == nullptr) {
        throw std::runtime_error("Invalid NULL pointer passed to c_load_grid");
    }
    return c_load_grid(path);  // ✅ Ensure passing a valid C-string
}

// Wrapper for Julia initialization
void init_julia_wrapper(py::list args) {
    int argc = args.size();
    char** argv = new char*[argc];

    for (int i = 0; i < argc; ++i) {
        std::string arg = py::cast<std::string>(args[i]);  // Convert Python object to std::string
        argv[i] = new char[arg.size() + 1];  // Allocate memory
        std::strcpy(argv[i], arg.c_str());   // Copy string
    }

    init_julia(argc, argv);  // Call Julia initialization

    // Free allocated memory
    for (int i = 0; i < argc; ++i) {
        delete[] argv[i];
    }
    delete[] argv;
}

// Wrapper for Julia shutdown
void shutdown_julia_wrapper(int retcode) {
    shutdown_julia(retcode);
}

// Pybind11 module definition
PYBIND11_MODULE(pypm2c, m) {
    m.doc() = "Python bindings for libpowermodelscompiled"; // Module docstring
    m.def("init_julia", &init_julia_wrapper,"Initialize julia");
    m.def("shutdown_julia",&shutdown_julia_wrapper,"Shutdown julia");
    m.def("increment32", &increment32, "Increment a 32-bit integer");
    m.def("increment64", &increment64, "Increment a 64-bit integer");
    m.def("c_load_grid", &c_load_grid_wrapper, "Load grid from a given file path");

    // Wrap `c_solve_power_flow` to return a Python string
    m.def("c_solve_power_flow", &solve_power_flow_wrapper, "Solve power flow and return JSON result");
}
