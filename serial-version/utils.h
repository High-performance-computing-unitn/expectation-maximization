#ifndef EM_PROJECT_UTILS_SERIAL
#define EM_PROJECT_UTILS_SERIAL

// calculate the inverse of matrix
double inverse(double *A, double *inv, int n); // Function to calculate and store inverse

// calculate matrix-vector multiplication
void matmul(double *mat, double *vec, double *res, int D);

// calculate the dot product
double dotProduct(double *a, double *b, int D);

// standardize the training data
void standardize(double* data, int N, int D);

#endif 