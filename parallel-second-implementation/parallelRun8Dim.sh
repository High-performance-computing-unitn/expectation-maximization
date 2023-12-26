#!/bin/bash

#PBS -l select=1:ncpus=64

#PBS -l walltime=00:01:00

#PBS -q short_cpuQ

module load mpich-3.2

echo "execution with 2 cores"

# arguments are                     executable                                   N    D K iter filepath
mpiexec -n 2 expectation-maximization/parallel-second-implementation/parallelRun 4000 8 4 200 "expectation-maximization/data-generator/N4000_K4_D8.csv"

echo "---end---"

echo "execution with 4 cores"

# arguments are                     executable                                   N    D K iter filepath
mpiexec -n 4 expectation-maximization/parallel-second-implementation/parallelRun 4000 8 4 200 "expectation-maximization/data-generator/N4000_K4_D8.csv"

echo "---end---"

echo "execution with 8 cores"

# arguments are                     executable                                   N    D K iter filepath
mpiexec -n 8 expectation-maximization/parallel-second-implementation/parallelRun 4000 8 4 200 "expectation-maximization/data-generator/N4000_K4_D8.csv"

echo "---end---"

echo "execution with 16 cores"

# arguments are                     executable                                   N    D K iter filepath
mpiexec -n 16 expectation-maximization/parallel-second-implementation/parallelRun 4000 8 4 200 "expectation-maximization/data-generator/N4000_K4_D8.csv"

echo "---end---"

echo "execution with 32 cores"

# arguments are                     executable                                   N    D K iter filepath
mpiexec -n 32 expectation-maximization/parallel-second-implementation/parallelRun 4000 8 4 200 "expectation-maximization/data-generator/N4000_K4_D8.csv"

echo "---end---"

echo "execution with 64 cores"

# arguments are                     executable                                   N    D K iter filepath
mpiexec -n 64 expectation-maximization/parallel-second-implementation/parallelRun 4000 8 4 200 "expectation-maximization/data-generator/N4000_K4_D8.csv"

echo "---end---"