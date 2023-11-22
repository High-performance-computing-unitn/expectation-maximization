#!/bin/bash

#PBS -l select=1:ncpus=1:mem=2gb

#PBS -l walltime=03:00:00

#PBS -q short_cpuQ

module load mpich-3.2
# arguments are                                                 N   D K iter filepath
mpiexec -n 1 /expectation-maximization/serial-version/serialRun 800 5 4 10 "filepath"