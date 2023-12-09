#!/bin/bash

#PBS -l select=1:ncpus=1:mem=2gb

#PBS -l walltime=03:00:00

#PBS -q short_cpuQ

# arguments are                                     N      D K iter filepath
./expectation-maximization/serial-version/serialRun 625000 4 5 200 "expectation-maximization/data-generator/N625000_K5_D4.csv"