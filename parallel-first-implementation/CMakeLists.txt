cmake_minimum_required(VERSION 3.23)
project(em_project C)

set(CMAKE_C_STANDARD 99)

add_executable(em_project main.c linear_op.h constants.h linear_op.c e_step.h e_step.c m_step.h m_step.c em_algorithm.h em_algorithm.c reader.h reader.c utils.h utils.c)
