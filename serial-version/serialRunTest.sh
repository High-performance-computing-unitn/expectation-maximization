#!/bin/bash

#PBS -l select=1:ncpus=1:mem=2gb

#PBS -l walltime=03:00:00

#PBS -q short_cpuQ

# arguments are                                                 N   D K iter filepath
./expectation-maximization/serial-version/serialRun 800 3 4 50 "expectation-maximization/data-generator/N800_K4_D3.csv"