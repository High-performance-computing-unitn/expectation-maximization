#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

/*
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

float matrix_det(float *m, int n)
{
    if (n > 3)
    {
        int n2 = n * n;
        float *matrix = (float *)malloc(n2 * sizeof(float));
        if (matrix)
        {
#pragma omp parallel for
            for (int i = 0; i < n2; i++)
                matrix[i] = m[i];

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
        else return 0.;
    }
    else if (n == 3)
    {
        return (m[0] * (m[4] * m[8] - m[5] * m[7]) - m[1] * (m[3] * m[8] - m[5] * m[6]) + m[2] * (m[3] * m[7] - m[4] * m[6]));
    }
    else if (n == 2)
    {
        return (m[0] * m[3] - m[1] * m[2]);
    }
    else if (n == 1)
    {
        return m[0];
    }
    else return 0.;
}

void set_matrix(float *m, int n)
{
    int n2 = n * n;
#pragma omp parallel for
    for (int i = 0; i < n2; i++)
        m[i] = (float)rand() / (float)(RAND_MAX / n);
}

int main()
{
    int MatDim = 10;
    int MatSize = MatDim * MatDim;

    float *matrix = (float *)malloc(MatSize * sizeof(float));

    if (matrix)
    {
        set_matrix(matrix, MatDim);

        int split = MatDim;
        for (int i = 0; i < MatSize; i++)
        {
            if (i == split)
            {
                printf("\n");
                split = split + MatDim;
            }

            printf("%f ", matrix[i]);
        }

        clock_t start = clock();

        float det = matrix_det(matrix, MatDim);

        clock_t end = clock();
        printf("\nDeterminant took: %f seconds and resulted in: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC, det);

        free(matrix);
    }
}