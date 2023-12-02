#ifndef EM_PROJECT_LINEAR_OP_H
#define EM_PROJECT_LINEAR_OP_H

// calculate the inverse of matrix
void inverse(double *A, double *inv, double *det, int n);

// calculate matrix-vector multiplication
void matmul(double *mat, double *vec, double *res, int D);

// calculate the dot product
double dotProduct(double *a, double *b, int D);

// standardize the training data
void standardize(double* data, int N, int D);

#endif //EM_PROJECT_LINEAR_OP_H
