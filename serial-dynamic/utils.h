#ifndef EM_PROJECT_UTILS_PARALLEL
#define EM_PROJECT_UTILS_PARALLEL

float *allocate_array(int rows);
void free_matrix(float **matrix, int rows);
float **allocate_matrix(int rows, int cols);
void free_3d_array(float ***data, int xlen, int ylen);
float ***allocate_3d_array(int xlen, int ylen, int zlen);
void inverse(float **A, float **inverse, float* det);
void matmul(float **mat, float *vec, float *res);
float dotProduct(float *a, float *b);
void standardize(float **data);

#endif 