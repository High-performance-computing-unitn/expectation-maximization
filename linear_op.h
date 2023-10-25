#ifndef EM_PROJECT_LINEAR_OP_H
#define EM_PROJECT_LINEAR_OP_H

#include "constants.h"

void getCofactor(float A[D][D], float temp[D][D], int p, int q, int n);

float determinant(float A[D][D], int n); // Recursive function for finding determinant of matrix.

void adjoint(float A[D][D], float adj[D][D]); // Function to get adjoint of A[N][N] in adj[N][N].

void inverse(float A[D][D], float inverse[D][D], float* det); // Function to calculate and store inverse

void matmul(float mat[D][D], float vec[D], float res[D]);

float dotProduct(float a[D], float b[D]);

#endif //EM_PROJECT_LINEAR_OP_H
