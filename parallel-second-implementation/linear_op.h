#ifndef EM_PROJECT_LINEAR_OP_DYNAMIC_PARALLEL
#define EM_PROJECT_LINEAR_OP_DYNAMIC_PARALLEL

#include "constants.h"

// calculate the determinant
double determinant(double *m, int n, int starting_index);

// calculate the inverse of matrix
void inverse(double *cov, double *inv, double *det, int n, int starting_index);

// calculate matrix-vector multiplication
void matmul(double *mat, double *vec, double *res);

// calculate the dot product
double dotProduct(double *a, double *b);

// standardize the training data
void standardize(Sample *samples, int sample_size);

#endif
