#!/bin/bash

#PBS -l select=1:ncpus=4:mem=2gb

#PBS -l walltime=03:00:00

#PBS -q short_cpuQ

module load mpich-3.2
# arguments are                     executable                                   N   D K iter filepath
mpiexec -n 4 expectation-maximization/parallel-second-implementation/parallelRun 800 3 4 20 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "----------------------"

mpiexec -n 4 expectation-maximization/parallel-second-implementation/parallelRun 800 3 4 20 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "----------------------"

mpiexec -n 4 expectation-maximization/parallel-second-implementation/parallelRun 800 3 4 20 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "----------------------"

mpiexec -n 4 expectation-maximization/parallel-second-implementation/parallelRun 800 3 4 20 "expectation-maximization/data-generator/N800_K4_D3.csv"

echo "----------------------"