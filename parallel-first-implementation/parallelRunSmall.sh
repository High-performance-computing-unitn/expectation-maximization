#!/bin/bash

#PBS -l select=1:ncpus=80:mem=1gb

#PBS -l walltime=00:20:00

#PBS -q short_cpuQ

module load mpich-3.2

echo "execution with 80 cores"

# arguments are                     executable                                  N      D K iter filepath
mpiexec -n 80 expectation-maximization/parallel-first-implementation/parallelRun 250000 4 5 200 "expectation-maximization/data-generator/N250000_K5_D4.csv"

echo "---end---"