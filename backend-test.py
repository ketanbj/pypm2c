import os
import numpy as np
import grid2op
from typing import Optional, Tuple, Union

from grid2op.Backend import Backend

from powerModelsBackend import PowerModelsBackend

#backend = PowerModelsBackend()

# to test
#backend.load_data("case5.m")


if __name__ == "__main__":
    path_grid2op = grid2op.__file__
    path_data_test = os.path.join(os.path.split(path_grid2op)[0], "data")
    
    env_name = "rte_case5_example"
    # one of:
    # - rte_case5_example: the grid in the documentation (completely fake grid)
    # - l2rpn_case14_sandbox: inspired from IEEE 14
    # - l2rpn_neurips_2020_track1: inspired from IEEE 118 (only a third of it)
    # - l2rpn_wcci_2022_dev: inspired from IEEE 118 (entire grid)
    
    a_grid = os.path.join(path_data_test, env_name, "grid.json")
    
    backend = PowerModelsBackend()
    backend.load_grid(path=a_grid)
    
    # grid2op then performs basic check to make sure that the grid is "consistent"
    backend.assert_grid_correct()
    
    # for example
    print(f"Name of the loads, seen in grid2op: {type(backend).name_load}")
    print(f"Id of substation, for each load: {type(backend).load_to_subid}")
    print(f"Position in the substation topology vector, for each load: {type(backend).load_to_sub_pos}")
    print(f"Position in the global topology vector, for each load: {type(backend).load_pos_topo_vect}")