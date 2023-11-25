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

            free(matrix);
            return det;
        }
        else
            return 0.;
    }
    else if (n == 3)
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

void generate_identity(float **matrix, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
}

void copy_matrix(float **copy, float *matrix, int size, int starting_index)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            copy[i][j] = matrix[starting_index + i * size + j];
}

void inverse(float *matrix, float *inv, int size, int starting_index)
{
    float **input_matrix = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        input_matrix[i] = (float *)malloc(size * sizeof(float));

    float **inverse = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        inverse[i] = (float *)malloc(size * sizeof(float));

    copy_matrix(input_matrix, matrix, size, starting_index);

    generate_identity(inverse, size);
    for (int i = 0; i < size; i++)
    {
        if (input_matrix[i][i] == 0)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (input_matrix[j][i] != 0.0)
                {
                    float *tmp = (float *)malloc(size * sizeof(float));
                    tmp = input_matrix[i];
                    input_matrix[i] = input_matrix[j];
                    input_matrix[j] = tmp;

                    free(tmp);
                    break;
                }
                if (j == size - 1)
                {
                    printf("Inverse does not exist for this matrix");
                    exit(0);
                }
            }
        }
        float scale = input_matrix[i][i];
        for (int col = 0; col < size; col++)
        {
            input_matrix[i][col] = input_matrix[i][col] / scale;
            inverse[i][col] = inverse[i][col] / scale;
        }
        if (i < size - 1)
        {
            for (int row = i + 1; row < size; row++)
            {
                float factor = input_matrix[row][i];
                for (int col = 0; col < size; col++)
                {
                    input_matrix[row][col] -= factor * input_matrix[i][col];
                    inverse[row][col] -= factor * inverse[i][col];
                }
            }
        }
    }
    for (int zeroing_col = size - 1; zeroing_col >= 1; zeroing_col--)
    {
        for (int row = zeroing_col - 1; row >= 0; row--)
        {
            float factor = input_matrix[row][zeroing_col];
            for (int col = 0; col < size; col++)
            {
                input_matrix[row][col] -= factor * input_matrix[zeroing_col][col];
                inverse[row][col] -= factor * inverse[zeroing_col][col];
            }
        }
    }

    for (int i = 0; i < D; i++)
        for (int j = 0; j < D; j++)
            inv[i * D + j] = inverse[i][j];

    for (int i = 0; i < size; i++)
    {
        free(inverse[i]);
        free(input_matrix[i]);
    }
    free(inverse);
    free(input_matrix);
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

    free(mean);
    free(stdDev);
}