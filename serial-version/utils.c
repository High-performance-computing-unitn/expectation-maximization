#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float determinant(float *A, int n) {
    float det = 0;

    // Base case: if the matrix contains a single element
    if (n == 1)
        return A[0];

    float *temp = (float *)malloc(n * n  * sizeof(float));

    int sign = 1;

    for (int f = 0; f < n; f++) {
        // Getting the cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        det += sign * A[f] * determinant(temp, n - 1);

        // Terms are to be added with alternate sign
        sign = -sign;
    }

    free(temp);

    return det;
}


void adjoint(float *A, float *adj, int n) {
    if (n == 1) {
        adj[0] = 1;
        return;
    }

    // Temp is used to store cofactors of A[][]
    int sign = 1;
    float *temp = (float *)malloc(n * n  * sizeof(float));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Get the cofactor of A[i][j]
            getCofactor(A, temp, i, j, n);

            // Sign of adj[j][i] is positive if the sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchange rows and columns to get the
            // transpose of the cofactor matrix
            adj[j * n + i] = (sign) * (determinant(temp, n - 1));
        }
    }

    free(temp);
}


void inverse(float *A, float *inv, float *det, int n) {
    // Find the determinant of A[][]
    *det = determinant(A, n);

    // Find the adjoint
    float *adj = (float *)malloc(n * n * sizeof(float));
    adjoint(A, adj, n);

    // Find the inverse using the formula "inverse(A) = adj(A)/det(A)"
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i * n + j] = adj[j * n + i] / *det;
        }
    }

    free(adj);
}


/*
    Function that performs matrix vector multiplication
    and stores the result in the res vector passed as an argument.
*/
void matmul(float *mat, float *vec, float *res, int D) {
    for (int i = 0; i < D; i++) {
        res[i] = 0;
        for (int j = 0; j < D; j++) {
            res[i] += mat[i * D + j] * (float)vec[j];
        }
    }
}


/*
    Function that calculates the dot product between two vectors
    and returns the results.
*/
float dotProduct(float *a, float *b, int D) {
    float result = 0.0;
    for (int i = 0; i < D; i++) {
        result += a[i] * b[i];
    }
    return result;
}


/*
    Function that performs z-score normalization on the training examples.
*/
void standardize(float* data, int N, int D) {
    // Calculate the mean for each dimension
    float* mean = malloc(D * sizeof(float ));
    for (int j = 0; j < D; j++) {
        mean[j] = 0.0;
        for (int i = 0; i < N; i++) {
            mean[j] += data[i * D + j];
        }
        mean[j] /= N;
    }

    // Calculate the standard deviation for each dimension
    float* stdDev = malloc(D * sizeof(float ));
    for (int j = 0; j < D; j++) {
        stdDev[j] = 0.0;
        for (int i = 0; i < N; i++) {
            stdDev[j] += pow(data[i * D + j] - mean[j], 2);
        }
        stdDev[j] = sqrt(stdDev[j] / (N - 1));
    }

    // Perform standardization
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            data[i * D + j] = (data[i * D + j] - mean[j]) / stdDev[j];
        }
    }
    free(mean);
    free(stdDev);
}
