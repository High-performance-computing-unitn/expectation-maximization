#!/bin/bash

#PBS -l select=1:ncpus=1:mem=2gb

#PBS -l walltime=03:00:00

#PBS -q short_cpuQ

# arguments are                                     N      D K iter filepath
./expectation-maximization/serial-version/serialRun 125000 3 5 200 "expectation-maximization/data-generator/N125000_K5_D3.csv"