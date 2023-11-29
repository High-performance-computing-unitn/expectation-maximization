#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "constants.h"

/*
detrminant code
https://matematicamente.it/forum/viewtopic.php?f=15&t=145130
*/

float my_abs(float a)
{
    return (a < 0.) ? -a : a;
}

float factorize(float *m, int n)
{
    float parity = 1.;

    for (int k = 0; k < n - 1; k++)
    {
        float max = my_abs(m[k * n + k]);
        int ip = k;
        for (int i = k + 1; i < n; i++)
        {
            float t = my_abs(m[i * n + k]);
            if (t > max)
            {
                max = t;
                ip = i;
            }
        }

        if (max == 0.)
        {
            return 0.;
        }

        if (ip != k)
        {
            parity *= -1;
#pragma omp parallel for
            for (int i = 0; i < n; i++)
            {
                float t = m[k * n + i];
                m[k * n + i] = m[ip * n + i];
                m[ip * n + i] = t;
            }
        }

        float pe = m[k * n + k];
#pragma omp parallel for
        for (int i = k + 1; i < n; i++)
            m[i * n + k] /= pe;

#pragma omp parallel for
        for (int i = k + 1; i < n; i++)
        {
            float mik = m[i * n + k];
            for (int j = k + 1; j < n; j++)
                m[i * n + j] -= mik * m[k * n + j];
        }
    }

    return parity;
}

float determinant(float *m, int n, int starting_index)
{
    if (n > 3)
    {
        int n2 = n * n;
        float *matrix = (float *)malloc(n2 * sizeof(float));
        if (matrix)
        {
#pragma omp parallel for
            for (int i = 0; i < n2; i++)
                matrix[i] = m[starting_index + i];

            float det = factorize(matrix, n);

            if (det != 0)
            {
#pragma omp parallel for reduction(* : det)
                for (int i = 0; i < n; i++)
                {
                    int ind = i * n + i;
                    float value = matrix[ind];
                    det *= value;
                }
            }

            if (matrix)
                free(matrix);
            return det;
        }
        else
            return 0.;
    }
    else if (n == 3)
    {
        return (m[starting_index] * (m[starting_index + 4] * m[starting_index + 8] - m[starting_index + 5] * m[starting_index + 7]) - m[starting_index + 1] * (m[starting_index + 3] * m[starting_index + 8] - m[starting_index + 5] * m[starting_index + 6]) + m[starting_index + 2] * (m[starting_index + 3] * m[starting_index + 7] - m[starting_index + 4] * m[starting_index + 6]));
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

void getCofactor(float *cov, float *temp, int p, int q, int n, int starting_index)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            // Copying into the temporary matrix only those
            // elements that are not in the given row and column
            if (row != p && col != q)
            {
                temp[i * (n - 1) + j] = cov[starting_index + row * n + col];
                j++;

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

void adjoint(float *cov, float *adj, int n, int starting_index)
{
    if (n == 1)
    {
        adj[0] = 1;
        return;
    }

    // Temp is used to store cofactors of A[][]
    int sign = 1;
    float *temp = (float *)malloc(n * n * sizeof(float));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Get the cofactor of A[i][j]
            getCofactor(cov, temp, i, j, n, starting_index);

            // Sign of adj[j][i] is positive if the sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchange rows and columns to get the
            // transpose of the cofactor matrix
            adj[j * n + i] = (sign) * (determinant(temp, n - 1, starting_index));
        }
    }

    free(temp);
}

void inverse(float *cov, float *inv, float *det, int n, int starting_index)
{
    // Find the determinant of A[][]
    *det = determinant(cov, n, starting_index);

    // Find the adjoint
    float *adj = (float *)malloc(n * n * sizeof(float));
    adjoint(cov, adj, n, starting_index);

    // Find the inverse using the formula "inverse(A) = adj(A)/det(A)"
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i * n + j] = adj[j * n + i] / *det;

    free(adj);
}

/*
    Function that performs matrix vector multiplication
    and stores the result in the res vector passed as an argument.
*/
void matmul(float *mat, float *vec, float *res)
{
    for (int i = 0; i < D; i++)
    {
        res[i] = 0;
        for (int j = 0; j < D; j++)
            res[i] += mat[i * D + j] * (float)vec[j];
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
        result += a[i] * b[i];
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
            mean[j] += data[i].dimensions[j];
        mean[j] /= sample_size;
    }

    // Calculate the standard deviation for each dimension
    float *stdDev = (float *)malloc(D * sizeof(float));
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

    if (mean)
        free(mean);
    if (stdDev)
        free(stdDev);
}