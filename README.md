# pypm2c
python module for the [PowerModels.jl](https://github.com/lanl-ansi/PowerModels.jl) based Grid2Op created by wrapping up PowerModelsthe dynamic library generated as wrapper of  to be integrated as 

# organization

- This repository uses [pm2c](https://github.com/ketanbj/pm2c/) as submodule. pm2c is the repository containing a simple C wrapper over PowerModels.js and required build instructions to generate and test a dynamic library. It generates libpowermodelscompiled.so or libpowermodelscompiled.dylib
- Typical files needed to define a python module: setup.py, pyproject.toml
- pybind_libpowermodels.cpp contains the python bindings to call the functions in libpowermodelscompiled from python.
- pm2c-test.py is a simple test
- 

# pre-requisites

- Install Julia 1.11.1 or 1.11.2
- Set PATH: 
```export PATH=<path to>/julia/bin:$PATH```

If you installed Julia from a downloaded dmg on Mac, it looks something like this:

```export PATH=/Applications/Julia-1.11.app/Contents/Resources/julia/bin:$PATH```

If you are running on rogues gallery machines, loading the julia module will set up the PATH variable :

```module load julia/1.11.2```

# build

1. Clone the repository recursively:

```git clone --recursive https://github.com/ketanbj/pypm2c.git```


2. Build pm2c to generate libpowermodels:

```cd pypm2c/pm2c
    make
```

For detailed instructions refer to [pm2c](https://github.com/ketanbj/pm2c/) repository.

3. Build python module
   
```cd ..
  python3 -m venv venv
  source venv/bin/activate
  pip install --upgrade pip
  pip install pybind11
  python setup.py -v build_ext --inplace
```

This step will generate pypm2c.cpython-311-x86_64-linux-gnu.so in the current directory.

4. Test
   
```python pm2c-test.py```

Sample output:

```
python pm2c-test.py
Found c_load_grid:  True
Found c_solve_power_flow:  True
Loading grid from case5.m[warn | PowerModels]: The last 5 generator cost records will be ignored due to too few generator records.
[warn | PowerModels]: reversing the orientation of branch 6 (4, 3) to be consistent with other parallel branches
[warn | PowerModels]: bus 3 has an unrecongized bus_type 0, updating to bus_type 2
[warn | PowerModels]: the voltage setpoint on generator 4 does not match the value at bus 4
[warn | PowerModels]: the voltage setpoint on generator 1 does not match the value at bus 1
[warn | PowerModels]: the voltage setpoint on generator 5 does not match the value at bus 10
[warn | PowerModels]: the voltage setpoint on generator 2 does not match the value at bus 1
[warn | PowerModels]: the voltage setpoint on generator 3 does not match the value at bus 3
[info | PowerModels]: removing 1 cost terms from generator 4: [4000.0, 0.0]
[info | PowerModels]: removing 1 cost terms from generator 1: [1400.0, 0.0]
[info | PowerModels]: removing 1 cost terms from generator 5: [1000.0, 0.0]
[info | PowerModels]: removing 1 cost terms from generator 2: [1500.0, 0.0]
[info | PowerModels]: removing 1 cost terms from generator 3: [3000.0, 0.0]
Loaded grid from case5.m
c_load_grid returned: 1
Loading grid from case5.m[warn | PowerModels]: The last 5 generator cost records will be ignored due to too few generator records.
[warn | PowerModels]: reversing the orientation of branch 6 (4, 3) to be consistent with other parallel branches
[warn | PowerModels]: bus 3 has an unrecongized bus_type 0, updating to bus_type 2
[warn | PowerModels]: the voltage setpoint on generator 4 does not match the value at bus 4
[warn | PowerModels]: the voltage setpoint on generator 1 does not match the value at bus 1
[warn | PowerModels]: the voltage setpoint on generator 5 does not match the value at bus 10
[warn | PowerModels]: the voltage setpoint on generator 2 does not match the value at bus 1
[warn | PowerModels]: the voltage setpoint on generator 3 does not match the value at bus 3
[info | PowerModels]: removing 1 cost terms from generator 4: [4000.0, 0.0]
[info | PowerModels]: removing 1 cost terms from generator 1: [1400.0, 0.0]
[info | PowerModels]: removing 1 cost terms from generator 5: [1000.0, 0.0]
[info | PowerModels]: removing 1 cost terms from generator 2: [1500.0, 0.0]
[info | PowerModels]: removing 1 cost terms from generator 3: [3000.0, 0.0]
Min 1000 0_pg[5] + 4000 0_pg[4] + 1500 0_pg[2] + 3000 0_pg[3] + 1400 0_pg[1]
Subject to
 0_p[(5, 3, 4)] - ((3.023733968256992 0_vm[3]²) + (31.688961102861494 * ((0_vm[3]*0_vm[4]) * sin(-0_va[4] + 0_va[3]))) + (-3.7285371696827663 * ((0_vm[3]*0_vm[4]) * cos(-0_va[4] + 0_va[3])))) = 0
 0_q[(5, 3, 4)] - (((30.23428299322752 0_vm[3]²) - (31.688961102861494 * ((0_vm[3]*0_vm[4]) * cos(-0_va[4] + 0_va[3])))) + (-3.7285371696827663 * ((0_vm[3]*0_vm[4]) * sin(-0_va[4] + 0_va[3])))) = 0
 0_p[(5, 4, 3)] - ((3.3336667000033335 0_vm[4]²) + (31.799781114623197 * ((0_vm[4]*0_vm[3]) * sin(0_va[4] - 0_va[3]))) + (-2.620337052065702 * ((0_vm[4]*0_vm[3]) * cos(0_va[4] - 0_va[3])))) = 0
 0_q[(5, 4, 3)] - (((33.33329700003334 0_vm[4]²) - (31.799781114623197 * ((0_vm[4]*0_vm[3]) * cos(0_va[4] - 0_va[3])))) + (-2.620337052065702 * ((0_vm[4]*0_vm[3]) * sin(0_va[4] - 0_va[3])))) = 0
 0_p[(4, 2, 3)] - ((9.167583425009166 0_vm[2]²) + (91.67583425009167 * ((0_vm[2]*0_vm[3]) * sin(0_va[2] - 0_va[3]))) + (-9.167583425009166 * ((0_vm[2]*0_vm[3]) * cos(0_va[2] -
.
.
.
iter    objective    inf_pr   inf_du lg(mu)  ||d||  lg(rg) alpha_du alpha_pr  ls
  10  1.8340458e+04 9.38e-03 7.62e+01  -1.0 8.43e-01    -  1.30e-01 1.00e+00h  1
  11  1.8301363e+04 8.43e-03 8.60e-01  -1.0 1.65e+00    -  1.00e+00 1.00e+00f  1
  12  1.8275704e+04 3.77e-03 1.82e-01  -1.7 7.47e-01    -  1.00e+00 9.78e-01h  1
  13  1.8270178e+04 4.68e-05 8.96e-02  -2.5 1.98e-01    -  9.91e-01 1.00e+00h  1
  14  1.8270088e+04 4.43e-06 3.93e-02  -2.5 5.37e-02    -  1.00e+00 1.00e+00h  1
  15  1.8270119e+04 3.56e-08 2.00e-03  -2.5 2.67e-03    -  1.00e+00 1.00e+00h  1
  16  1.8269149e+04 2.06e-06 1.42e-03  -3.8 3.21e-02    -  1.00e+00 1.00e+00f  1
  17  1.8269110e+04 1.33e-06 3.87e+00  -5.7 5.30e-03    -  1.00e+00 8.05e-01h  1
  18  1.8269103e+04 4.79e-07 8.51e-03  -5.7 2.80e-03    -  1.00e+00 1.00e+00f  1
  19  1.8269103e+04 6.24e-10 7.38e-04  -5.7 3.86e-04    -  1.00e+00 1.00e+00h  1
iter    objective    inf_pr   inf_du lg(mu)  ||d||  lg(rg) alpha_du alpha_pr  ls
  20  1.8269103e+04 6.15e-12 3.76e-07  -5.7 3.83e-05    -  1.00e+00 1.00e+00h  1
In iteration 20, 1 Slack too small, adjusting variable bound
  21  1.8269103e+04 7.56e-10 1.83e-02  -8.6 1.05e-04    -  1.00e+00 9.89e-01h  1
  22  1.8269103e+04 7.17e-14 3.50e-08  -8.6 3.44e-06    -  1.00e+00 1.00e+00h  1
  23  1.8269103e+04 2.20e-14 1.45e-12  -8.6 4.94e-10    -  1.00e+00 1.00e+00h  1

Number of Iterations....: 23

                                   (scaled)                 (unscaled)
Objective...............:   4.5672756806972188e+02    1.8269102722788874e+04
Dual infeasibility......:   1.4458290504978464e-12    5.7833162019913855e-11
Constraint violation....:   1.4209433629730485e-14    2.1982415887578100e-14
Variable bound violation:   1.9004002371758588e-08    1.9004002371758588e-08
Complementarity.........:   2.5059111149517954e-09    1.0023644459807181e-07
Overall NLP error.......:   2.5059111149517954e-09    1.0023644459807181e-07


Number of objective function evaluations             = 24
Number of objective gradient evaluations             = 24
Number of equality constraint evaluations            = 24
Number of inequality constraint evaluations          = 24
Number of equality constraint Jacobian evaluations   = 24
Number of inequality constraint Jacobian evaluations = 24
Number of Lagrangian Hessian evaluations             = 23
Total seconds in IPOPT                               = 0.739

EXIT: Optimal Solution Found.

```







