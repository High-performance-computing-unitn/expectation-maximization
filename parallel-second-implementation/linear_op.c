#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "constants.h"

/*
 * Code for matrix inverse taken from
 * https://www.geeksforgeeks.org/adjoint-inverse-matrix/
 * Code for determinant taken from
 * https://matematicamente.it/forum/viewtopic.php?f=15&t=145130
 */

double d_abs(double d)
{
    return (d < 0.) ? -d : d;
}

double factorize(double *matrix, int n)
{
    double parity = 1.;

    for (int k = 0; k < n - 1; k++)
    {
        double max = d_abs(matrix[k * n + k]);
        int index = k;
        for (int i = k + 1; i < n; i++)
        {
            double t = d_abs(matrix[i * n + k]);
            if (t > max)
            {
                max = t;
                index = i;
            }
        }

        if (max == 0.)
            return 0.;

        if (index != k)
        {
            parity *= -1;
            #pragma omp parallel for
            for (int i = 0; i < n; i++)
            {
                double t = matrix[k * n + i];
                matrix[k * n + i] = matrix[index * n + i];
                matrix[index * n + i] = t;
            }
        }

        double pe = matrix[k * n + k];
        #pragma omp parallel for
        for (int i = k + 1; i < n; i++)
            matrix[i * n + k] /= pe;

        #pragma omp parallel for
        for (int i = k + 1; i < n; i++)
        {
            double matrix_i_k = matrix[i * n + k];
            for (int j = k + 1; j < n; j++)
                matrix[i * n + j] -= matrix_i_k * matrix[k * n + j];
        }
    }

    return parity;
}

double determinant(double *m, int n, int starting_index)
{
    // if matrix is grater than 3x3 compute as follows
    if (n > 3)
    {
        int n2 = n * n;
        double *matrix = (double *)calloc(n2, sizeof(double));
        if (matrix)
        {
            // copy the input matrix with threads to avoid changing its values
            #pragma omp parallel for
            for (int i = 0; i < n2; i++)
                matrix[i] = m[starting_index + i];

            double det = factorize(matrix, n); // factorize matrix

            if (det != 0)
            {
                // if the determinant is not zero each thread compute its det and then multiply the result of each thread
                #pragma omp parallel for reduction(* : det)
                for (int i = 0; i < n; i++)
                {
                    int ind = i * n + i;
                    double value = matrix[ind];
                    det *= value;
                }
            }
            free(matrix);
            return det;
        }
        else
            return 0.;
    }
    else if (n == 3) // if matrix is less then or equal to 3x3 in size compute determinant by hand
    {
        return (m[starting_index] * (m[starting_index + 4] * m[starting_index + 8] - m[starting_index + 5] * m[starting_index + 7])
                - m[starting_index + 1] * (m[starting_index + 3] * m[starting_index + 8] - m[starting_index + 5] * m[starting_index + 6])
                + m[starting_index + 2] * (m[starting_index + 3] * m[starting_index + 7] - m[starting_index + 4] * m[starting_index + 6]));
    }
    else if (n == 2)
    {
        return (m[starting_index] * m[starting_index + 3] - m[starting_index + 1] * m[starting_index + 2]);
    }
    else if (n == 1)
    {
        return m[starting_index];
    }
    else
        return 0.;
}

void getCofactor(double *cov, double *temp, int p, int q, int n, int starting_index)
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++) // Looping for each element of the matrix
    {
        for (int col = 0; col < n; col++)
        {
            // Copying into the temporary matrix only those elements that are not in the given row and column
            if (row != p && col != q)
            {
                temp[i * (n - 1) + j] = cov[starting_index + row * n + col];
                j++;

                // Row is filled, so increase row index and reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void adjoint(double *cov, double *adj, int n, int starting_index)
{
    if (n == 1)
    {
        adj[0] = 1;
        return;
    }

    // Temp is used to store cofactors of A[][]
    int sign = 1;
    double *temp = (double *)calloc(n * n, sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Get the cofactor of A[i][j]
            getCofactor(cov, temp, i, j, n, starting_index);

            // Sign of adj[j][i] is positive if the sum of row and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchange rows and columns to get the transpose of the cofactor matrix
            adj[j * n + i] = (sign) * (determinant(temp, n - 1, starting_index));
        }
    }

    free(temp);
}

/*
    Function that computes the inverse of the imput matrix and calculate its determinant
*/
void inverse(double *cov, double *inv, double *det, int n, int starting_index)
{
    // Find the determinant of A[][]
    *det = determinant(cov, n, starting_index);

    // Find the adjoint
    double *adj = (double *)calloc(n * n, sizeof(double));
    adjoint(cov, adj, n, starting_index);

    // Find the inverse using the formula "inverse(A) = adj(A)/det(A)"
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i * n + j] = adj[j * n + i] / *det;

    free(adj);
}

/*
    Function that performs matrix vector multiplication and stores the result in the res vector passed as an argument.
*/
void matmul(double *mat, double *vec, double *res)
{
    for (int i = 0; i < D; i++)
    {
        res[i] = 0;
        for (int j = 0; j < D; j++)
            res[i] += mat[i * D + j] * (double)vec[j];
    }
}

/*
    Function that calculates the dot product between two vectors and returns the results.
*/
double dotProduct(double *a, double *b)
{
    double result = 0.0;
    for (int i = 0; i < D; i++)
        result += a[i] * b[i];
    return result;
}

/*
    Function that performs z-score normalization on the training examples.
*/
void standardize(Sample *data, int sample_size)
{
    // Calculate the mean for each dimension
    double *mean = (double *)calloc(D, sizeof(double));
    for (int j = 0; j < D; j++)
    {
        mean[j] = 0.0;
        for (int i = 0; i < sample_size; i++)
            mean[j] += data[i].dimensions[j];
        mean[j] /= sample_size;
    }

    // Calculate the standard deviation for each dimension
    double *stdDev = (double *)calloc(D, sizeof(double));
    for (int j = 0; j < D; j++)
    {
        stdDev[j] = 0.0;
        for (int i = 0; i < sample_size; i++)
            stdDev[j] += pow(data[i].dimensions[j] - mean[j], 2);
        stdDev[j] = sqrt(stdDev[j] / (sample_size - 1));
    }

    // Perform standardization
    for (int i = 0; i < sample_size; i++)
        for (int j = 0; j < D; j++)
            data[i].dimensions[j] = (data[i].dimensions[j] - mean[j]) / stdDev[j];

    free(mean);
    free(stdDev);
}