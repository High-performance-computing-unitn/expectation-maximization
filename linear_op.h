/*
      * Code for matrix inverse taken from
      * https://www.geeksforgeeks.org/adjoint-inverse-matrix/
*/


#ifndef EM_PROJECT_LINEAR_OP_H
#define EM_PROJECT_LINEAR_OP_H

#include <math.h>
#include "constants.h"

void getCofactor(float A[D][D], float temp[D][D], int p, int q,
                 int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */
float determinant(float A[D][D], int n)
{
    float det = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];

    float temp[D][D]; // To store cofactors

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++) {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        det += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return det;
}

// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(float A[D][D], float adj[D][D])
{
    if (D == 1) {
        adj[0][0] = 1;
        return;
    }

    // temp is used to store cofactors of A[][]
    int sign = 1;
    float temp[D][D];

    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, D);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign) * (determinant(temp, D - 1));
        }
    }
}

// Function to calculate and store inverse, returns false if
// matrix is singular
void inverse(float A[D][D], float inverse[D][D], float* det)
{
    // Find determinant of A[][]
    *det = determinant(A, D);

    // Find adjoint
    float adj[D][D];
    adjoint(A, adj);

    // Find Inverse using formula "inverse(A) =
    // adj(A)/det(A)"
    for (int i = 0; i < D; i++)
        for (int j = 0; j < D; j++)
            inverse[i][j] = adj[i][j] / *det;

}


void matmul(float mat[D][D], float vec[D], float res[D]) {
    for (int i = 0; i < D; i++) {
        res[i] = 0;
        for (int j = 0; j < D; j++) {
            res[i] += mat[i][j]*(float)vec[j];
        }
    }
}


float dotProduct(float a[D], float b[D]) {
    float result = 0.0;
    for (int i = 0; i < D; i++) {
        result += a[i] * b[i];
    }
    return result;
}


float gaussian(float x[D], float mean[D], float cov[D][D]) {
    // x - mean
    float x_u[D];
    for (int i = 0; i < D; i++) {
        x_u[i] = x[i] - mean[i];
    }

    float det;
    float inv[D][D];
    inverse(cov, inv, &det);

    float x_u_inv[D];
    matmul(inv, x, x_u_inv);
    float in_exp = dotProduct(x_u_inv, x);
    in_exp = exp(-0.5 * in_exp);

    float out_exp = 1. / sqrt(pow(2 * M_PI, D) * det);

    return out_exp * in_exp;
}


void e_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float res[N][K]) {
    for (int i = 0; i < N; i++) {
        float p_x = 0.;
        float gaussians[K];
        for (int j = 0; j < K; j++) {
            float g = gaussian(X[i], mean[j], cov[j]) * weights[j];
            gaussians[j] = g;
            p_x += g;
        }

        for (int j = 0; j < K; j++) {
            float pij = gaussians[j] / p_x;
            res[i][j] = pij;
        }
    }
}


#endif //EM_PROJECT_LINEAR_OP_H
