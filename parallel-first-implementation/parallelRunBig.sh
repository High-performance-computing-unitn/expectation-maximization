#!/bin/bash

#PBS -l select=2:ncpus=1:mpiprocs=2 -l place=scatter

#PBS -l walltime=03:00:00

#PBS -q short_cpuQ

module load mpich-3.2

echo "execution with 1 core"

# arguments are                     executable                                  N       D K iter filepath
mpiexec -n 1 expectation-maximization/parallel-first-implementation/parallelRun 1250000 4 5 200 "expectation-maximization/data-generator/N1250000_K5_D4.csv"

echo "---end---"

echo "execution with 2 cores"

# arguments are                     executable                                  N       D K iter filepath
mpiexec -n 2 expectation-maximization/parallel-first-implementation/parallelRun 1250000 4 5 200 "expectation-maximization/data-generator/N1250000_K5_D4.csv"

echo "---end---"

# echo "execution with 4 cores"

# # arguments are                     executable                                  N   D K iter filepath
# mpiexec -n 4 expectation-maximization/parallel-first-implementation/parallelRun 1250000 4 5 200 "expectation-maximization/data-generator/N1250000_K5_D4.csv"

# echo "---end---"

# echo "execution with 8 cores"

# # arguments are                     executable                                  N   D K iter filepath
# mpiexec -n 8 expectation-maximization/parallel-first-implementation/parallelRun 1250000 4 5 200 "expectation-maximization/data-generator/N1250000_K5_D4.csv"

# echo "---end---"

# echo "execution with 16 cores"

# # arguments are                     executable                                  N   D K iter filepath
# mpiexec -n 16 expectation-maximization/parallel-first-implementation/parallelRun 1250000 4 5 200 "expectation-maximization/data-generator/N1250000_K5_D4.csv"

# echo "---end---"

# echo "execution with 32 cores"

# # arguments are                     executable                                  N   D K iter filepath
# mpiexec -n 32 expectation-maximization/parallel-first-implementation/parallelRun 1250000 4 5 200 "expectation-maximization/data-generator/N1250000_K5_D4.csv"

# echo "---end---"

# echo "execution with 64 cores"

# #arguments are                     executable                                  N   D K iter filepath
# mpiexec -n 64 expectation-maximization/parallel-first-implementation/parallelRun 1250000 4 5 200 "expectation-maximization/data-generator/N1250000_K5_D4.csv"

# echo "---end---"