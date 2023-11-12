#!/bin/bash

#PBS -l select=1:ncpus=4:mem=2gb

#PBS -l walltime=01:00:00

#PBS -q short_cpuQ

module load mpich-3.2
mpiexec -n 4 parallel-dynamic-test/parallelRun 800 5 4 50