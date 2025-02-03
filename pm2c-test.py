import pypm2c

import pypm2c

try:
    status = pypm2c.c_load_grid("case5.m")
    print(f"c_load_grid returned: {status}")
except Exception as e:
    print(f"Error calling c_load_grid: {e}")