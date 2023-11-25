#ifndef EM_PROJECT_LINEAR_OP_DYNAMIC_PARALLEL
#define EM_PROJECT_LINEAR_OP_DYNAMIC_PARALLEL

#include "constants.h"

float determinant(float *m, int n, int starting_index);

// calculate the inverse of matrix
void inverse(float *input_matrix, float *inverse, int size, int starting_index);

// calculate matrix-vector multiplication
void matmul(float *mat, float *vec, float *res);

// calculate the dot product
float dotProduct(float *a, float *b);

// standardize the training data
void standardize(Sample *samples, int sample_size);

#endif
