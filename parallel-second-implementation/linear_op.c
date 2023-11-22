#include <math.h>
#include <stdio.h>
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

void generate_identity(float **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
}

void copy_matrix(float **copy, float **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            copy[i][j] = matrix[i][j];
        }
    }
}

void inverse(float **matrix, float **inverse, int size)
{
    float **input_matrix = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        input_matrix[i] = (float *)malloc(size * sizeof(float));

    copy_matrix(input_matrix, matrix, size);

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

    for (int i = 0; i < size; i++)
    {
        free(input_matrix[i]);
    }
    free(input_matrix);
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