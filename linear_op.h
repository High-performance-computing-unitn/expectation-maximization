#ifndef EM_PROJECT_LINEAR_OP_H
#define EM_PROJECT_LINEAR_OP_H

#include "constants.h"

// get cofactor
void getCofactor(float A[D][D], float temp[D][D], int p, int q, int n);

// find the determinant of matrix.
float determinant(float A[D][D], int n);

// get adjoint of A[N][N] in adj[N][N].
void adjoint(float A[D][D], float adj[D][D]);

// calculate the inverse of matrix
void inverse(float A[D][D], float inverse[D][D], float* det); // Function to calculate and store inverse

// calculate matrix-vector multiplication
void matmul(float mat[D][D], float vec[D], float res[D]);

// calculate the dot product
float dotProduct(float a[D], float b[D]);

// standardize the training data
void standardize(float data[N][D]);

#endif //EM_PROJECT_LINEAR_OP_H
