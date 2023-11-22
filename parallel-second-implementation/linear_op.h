#ifndef EM_PROJECT_LINEAR_OP_DYNAMIC_PARALLEL
#define EM_PROJECT_LINEAR_OP_DYNAMIC_PARALLEL

#include "constants.h"

void matrix_flatten(float *flat_matrix, float **matrix, int row, int col);

void matrix_expand(float *flat_matrix, float **matrix, int row, int col);

void cube_flatten(float *flat_cube, float ***cube, int row, int col, int depth);

void cube_expand(float *flat_cube, float ***cube, int row, int col, int depth);

// calculate the inverse of matrix
void inverse(float **input_matrix, float **inverse, int size);

// calculate matrix-vector multiplication
void matmul(float **mat, float *vec, float *res);

// calculate the dot product
float dotProduct(float *a, float *b);

// standardize the training data
void standardize(Sample *data, int sample_size);

#endif
