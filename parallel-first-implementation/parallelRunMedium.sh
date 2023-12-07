#!/bin/bash

#PBS -l select=1:ncpus=64:mem=2gb

#PBS -l walltime=03:00:00

#PBS -q short_cpuQ

module load mpich-3.2

echo "execution with 2 cores"

# arguments are                     executable                                  N   D K iter filepath
mpiexec -n 2 expectation-maximization/parallel-first-implementation/parallelRun 800 3 4 200 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "---end---"

echo "execution with 4 cores"

# arguments are                     executable                                  N   D K iter filepath
mpiexec -n 4 expectation-maximization/parallel-first-implementation/parallelRun 800 3 4 200 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "---end---"

echo "execution with 8 cores"

# arguments are                     executable                                  N   D K iter filepath
mpiexec -n 8 expectation-maximization/parallel-first-implementation/parallelRun 800 3 4 200 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "---end---"

echo "execution with 16 cores"

# arguments are                     executable                                  N   D K iter filepath
mpiexec -n 16 expectation-maximization/parallel-first-implementation/parallelRun 800 3 4 200 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "---end---"

echo "execution with 32 cores"

# arguments are                     executable                                  N   D K iter filepath
mpiexec -n 32 expectation-maximization/parallel-first-implementation/parallelRun 800 3 4 200 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "---end---"

echo "execution with 64 cores"

# arguments are                     executable                                  N   D K iter filepath
mpiexec -n 64 expectation-maximization/parallel-first-implementation/parallelRun 800 3 4 200 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "---end---"