#ifndef EM_PROJECT_LINEAR_OP_H
#define EM_PROJECT_LINEAR_OP_H

double determinant(double *m, int n);

// calculate the inverse of matrix
void inverse(double *mat, double *inv, int size);

// calculate matrix-vector multiplication
void matmul(double *mat, double *vec, double *res, int D);

// calculate the dot product
double dotProduct(double *a, double *b, int D);

// standardize the training data
void standardize(double* data, int N, int comm_sz, int D);

#endif //EM_PROJECT_LINEAR_OP_H
