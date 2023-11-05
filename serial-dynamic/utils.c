#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"

int N, D;

float *allocate_array(int rows)
{
    float *array = (float *)malloc(rows * sizeof(float));
    if (array == NULL)
    {
        printf("can not allocate memory\n");
        exit(0);
    }

    return array;
}

void free_matrix(float **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

float **allocate_matrix(int rows, int cols)
{
    float **matrix = (float **)malloc(rows * sizeof(float *));
    if (matrix == NULL)
    {
        printf("Cannot allocate memory");
        exit(0);
    }
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (float *)malloc(cols * sizeof(float));
        if (matrix[i] == NULL)
        {
            printf("Cannot allocate memory");
            exit(0);
        }
    }

    return matrix;
}

void free_3d_array(float ***data, int xlen, int ylen)
{
    for (int i = 0; i < xlen; ++i)
    {
        if (data[i] != NULL)
        {
            for (int j = 0; j < ylen; ++j)
                free(data[i][j]);
            free(data[i]);
        }
    }
    free(data);
}

float ***allocate_3d_array(int xlen, int ylen, int zlen)
{
    float ***p;

    if ((p = malloc(xlen * sizeof *p)) == NULL)
    {
        perror("malloc 1");
        return NULL;
    }

    for (int i = 0; i < xlen; ++i)
        p[i] = NULL;

    for (int i = 0; i < xlen; ++i)
        if ((p[i] = malloc(ylen * sizeof *p[i])) == NULL)
        {
            perror("malloc 2");
            free_3d_array(p, xlen, ylen);
            return NULL;
        }

    for (int i = 0; i < xlen; ++i)
        for (int j = 0; j < ylen; ++j)
            p[i][j] = NULL;

    for (int i = 0; i < xlen; ++i)
        for (int j = 0; j < ylen; ++j)
            if ((p[i][j] = malloc(zlen * sizeof *p[i][j])) == NULL)
            {
                perror("malloc 3");
                free_3d_array(p, xlen, ylen);
                return NULL;
            }

    return p;
}

void getCofactor(float **A, float **temp, int p, int q, int n)
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


float determinant(float **A, int n) // Recursive function for finding determinant of matrix.
{
    float det = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];

    float **temp = allocate_matrix(D, D);

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++) {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        det += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    free_matrix(temp, D);
    return det;
}


void adjoint(float **A, float **adj) // Function to get adjoint of A[N][N] in adj[N][N].
{
    if (D == 1) {
        adj[0][0] = 1;
        return;
    }

    // temp is used to store cofactors of A[][]
    int sign = 1;
    float **temp = allocate_matrix(D, D);

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
    free_matrix(temp, D);
}

void inverse(float **A, float **inverse, float* det) // Function to calculate and store inverse
{
    // Find determinant of A[][]
    *det = determinant(A, D);

    // Find adjoint
    float **adj = allocate_matrix(D, D);
    adjoint(A, adj);

    // Find Inverse using formula "inverse(A) =
    // adj(A)/det(A)"
    for (int i = 0; i < D; i++)
        for (int j = 0; j < D; j++)
            inverse[i][j] = adj[i][j] / *det;

    free_matrix(adj, D);
}

void matmul(float **mat, float *vec, float *res) {
    for (int i = 0; i < D; i++) {
        res[i] = 0;
        for (int j = 0; j < D; j++) {
            res[i] += mat[i][j]*(float)vec[j];
        }
    }
}


/*
    Function that calculates the dot product between two vectors
    and returns the results.
*/
float dotProduct(float *a, float *b) {
    float result = 0.0;
    for (int i = 0; i < D; i++) {
        result += a[i] * b[i];
    }
    return result;
}

void standardize(float **data)
{
    // Calculate the mean for each dimension
    float mean[D];
    for (int j = 0; j < D; j++)
    {
        mean[j] = 0.0;
        for (int i = 0; i < N; i++)
        {
            mean[j] += data[i][j];
        }
        mean[j] /= N;
    }

    // Calculate the standard deviation for each dimension
    float stdDev[D];
    for (int j = 0; j < D; j++)
    {
        stdDev[j] = 0.0;
        for (int i = 0; i < N; i++)
        {
            stdDev[j] += pow(data[i][j] - mean[j], 2);
        }
        stdDev[j] = sqrt(stdDev[j] / (N - 1));
    }

    // Perform standardization
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < D; j++)
        {
            data[i][j] = (data[i][j] - mean[j]) / stdDev[j];
        }
    }
}