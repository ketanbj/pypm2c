import ctypes

# Load the shared library manually
lib = ctypes.CDLL("./pm2c/PowerModelsCompiled/lib//libpowermodelscompiled.so")

# Verify that the function exists
if not hasattr(lib, "c_load_grid"):
    raise RuntimeError("c_load_grid not found in shared library!")

print("Found c_load_grid: ", hasattr(lib, "c_load_grid"))
print("Found c_solve_power_flow: ", hasattr(lib, "c_solve_power_flow"))

import pypm2c

pypm2c.init_julia([])

try:
    status = pypm2c.c_load_grid("case5.m")
    print(f"c_load_grid returned: {status}")
except Exception as e:
    print(f"Error calling c_load_grid: {e}")

try:
    status = pypm2c.c_solve_power_flow("case5.m")
    print(f"c_load_grid returned: {status}")
except Exception as e:
    print(f"Error calling c_load_grid: {e}")

pypm2c.shutdown_julia(0);