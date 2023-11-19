#include <math.h>
#include <stdlib.h>
#include "constants.h"

void matrix_flatten(float *flat_matrix, float **matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            flat_matrix[i * row + j] = matrix[i][j];
        }
    }
}

void matrix_expand(float *flat_matrix, float **matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = flat_matrix[i * row + j];
        }
    }
}

void cube_flatten(float *flat_cube, float ***cube, int row, int col, int depth)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            for (int z = 0; z < depth; z++)
            {
                flat_cube[i + row * (j + col * z)] = cube[i][j][z];
            }
        }
    }
}

void cube_expand(float *flat_cube, float ***cube, int row, int col, int depth)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            for (int z = 0; z < depth; z++)
            {
                cube[i][j][z] = flat_cube[i + row * (j + col * z)];
            }
        }
    }
}

void getCofactor(float **A, float **temp, int p, int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
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

    float **temp = (float **)malloc(D * sizeof(float *)); // To store cofactors
    for (int i = 0; i < D; i++)
        temp[i] = (float *)malloc(D * sizeof(float));

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        det += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    for (int i = 0; i < D; i++)
    {
        free(temp[i]);
    }
    free(temp);

    return det;
}

void adjoint(float **A, float **adj) // Function to get adjoint of A[N][N] in adj[N][N].
{
    if (D == 1)
    {
        adj[0][0] = 1;
        return;
    }

    // temp is used to store cofactors of A[][]
    int sign = 1;
    float **temp = (float **)malloc(D * sizeof(float *));
    for (int i = 0; i < D; i++)
        temp[i] = (float *)malloc(D * sizeof(float));

    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < D; j++)
        {
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

    for (int i = 0; i < D; i++)
    {
        free(temp[i]);
    }
    free(temp);
}

void inverse(float **A, float **inverse, float *det) // Function to calculate and store inverse
{
    // Find determinant of A[][]
    *det = determinant(A, D);

    float **adj = (float **)malloc(D * sizeof(float *)); // Find adjoint
    for (int i = 0; i < D; i++)
        adj[i] = (float *)malloc(D * sizeof(float));

    adjoint(A, adj);

    // Find Inverse using formula "inverse(A) =
    // adj(A)/det(A)"
    for (int i = 0; i < D; i++)
        for (int j = 0; j < D; j++)
            inverse[i][j] = adj[i][j] / *det;

    for (int i = 0; i < D; i++)
    {
        free(adj[i]);
    }
    free(adj);
}

/*
    Function that performs matrix vector multiplication
    and stores the result in the res vector passed as an argument.
*/
void matmul(float **mat, float *vec, float *res)
{
    for (int i = 0; i < D; i++)
    {
        res[i] = 0;
        for (int j = 0; j < D; j++)
        {
            res[i] += mat[i][j] * (float)vec[j];
        }
    }
}

/*
    Function that calculates the dot product between two vectors
    and returns the results.
*/
float dotProduct(float *a, float *b)
{
    float result = 0.0;
    for (int i = 0; i < D; i++)
    {
        result += a[i] * b[i];
    }
    return result;
}

/*
    Function that performs z-score normalization on the training examples.
*/
void standardize(Sample *data, int sample_size)
{
    // Calculate the mean for each dimension
    float *mean = (float *)malloc(D * sizeof(float));
    for (int j = 0; j < D; j++)
    {
        mean[j] = 0.0;
        for (int i = 0; i < sample_size; i++)
        {
            mean[j] += data[i].dimensions[j];
        }
        mean[j] /= sample_size;
    }

    // Calculate the standard deviation for each dimension
    float *stdDev = (float *)malloc(D * sizeof(float));
    for (int j = 0; j < D; j++)
    {
        stdDev[j] = 0.0;
        for (int i = 0; i < sample_size; i++)
        {
            stdDev[j] += pow(data[i].dimensions[j] - mean[j], 2);
        }
        stdDev[j] = sqrt(stdDev[j] / (sample_size - 1));
    }

    // Perform standardization
    for (int i = 0; i < sample_size; i++)
    {
        for (int j = 0; j < D; j++)
        {
            data[i].dimensions[j] = (data[i].dimensions[j] - mean[j]) / stdDev[j];
        }
    }
    free(mean);
    free(stdDev);
}