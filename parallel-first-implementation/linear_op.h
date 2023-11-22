#ifndef EM_PROJECT_LINEAR_OP_H
#define EM_PROJECT_LINEAR_OP_H


// calculate the inverse of matrix
void inverse(float *A, float *inv, float *det, int n); // Function to calculate and store inverse

// calculate matrix-vector multiplication
void matmul(float *mat, float *vec, float *res, int D);

// calculate the dot product
float dotProduct(float *a, float *b, int D);

// standardize the training data
void standardize(float* data, int N, int D);


#endif //EM_PROJECT_LINEAR_OP_H
