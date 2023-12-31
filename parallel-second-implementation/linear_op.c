#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>

/*
 * Code for matrix inverse taken from
 * https://www.geeksforgeeks.org/adjoint-inverse-matrix/
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
#pragma omp parallel for num_threads(2)
            for (int i = 0; i < n; i++)
            {
                double t = matrix[k * n + i];
                matrix[k * n + i] = matrix[index * n + i];
                matrix[index * n + i] = t;
            }
        }

        double pe = matrix[k * n + k];
#pragma omp parallel for num_threads(2)
        for (int i = k + 1; i < n; i++)
            matrix[i * n + k] /= pe;

#pragma omp parallel for num_threads(2)
        for (int i = k + 1; i < n; i++)
        {
            double matrix_i_k = matrix[i * n + k];
            for (int j = k + 1; j < n; j++)
                matrix[i * n + j] -= matrix_i_k * matrix[k * n + j];
        }
    }

    return parity;
}

double determinant(double *m, int n)
{
    // if matrix is grater than 3x3 compute as follows
    if (n > 3)
    {
        int n2 = n * n;
        double *matrix = (double *)calloc(n2, sizeof(double));
        if (matrix)
        {
// copy the input matrix with threads to avoid changing its values
#pragma omp parallel for num_threads(2)
            for (int i = 0; i < n2; i++)
                matrix[i] = m[i];

            double det = factorize(matrix, n); // factorize matrix

            if (det != 0)
            {
// if the determinant is not zero each thread compute its det and then multiply the result of each thread
#pragma omp parallel for reduction(* : det) num_threads(2)
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
    else
        return 0.;
}

void getCofactor(double *A, double *temp, int p, int q, int n)
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++) // Looping for each element of the matrix
    {
        for (int col = 0; col < n; col++)
        {
            // Copying into the temporary matrix only those elements that are not in the given row and column
            if (row != p && col != q)
            {
                temp[i * (n - 1) + j] = A[row * n + col];
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

void generate_identity(double *inverse, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                inverse[i *size + j] = 1;
            else
                inverse[i *size + j] = 0;
        }
    }
}

void inverse(double *mat, double *inv, int size)
{
    double *input_matrix = calloc(size * size, sizeof(double));

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            input_matrix[i * size + j] = mat[i * size + j];
    
    generate_identity(inv, size);

    for (int i = 0; i < size; i++)
    {
        if (input_matrix[i * size + i] == 0)
        {
            // swap nearest subsequent row s.t input_matrix[i][i] != 0 after swapping
            for (int j = i + 1; j < size; j++)
            {
                if (input_matrix[j * size + i] != 0.0)
                {
                    for (int z = 0; z < size; z++)
                    {
                        double tmp = input_matrix[i * size + z];
                        input_matrix[i * size + z] = input_matrix[j * size + z];
                        input_matrix[j * size + z] = tmp;
                    }

                    break;
                }
                if (j == size - 1)
                {
                    printf("Inverse does not exist for this matrix");
                    exit(1);
                }
            }
        }
        double scale = input_matrix[i * size + i];
        for (int col = 0; col < size; col++)
        {
            input_matrix[i * size + col] = input_matrix[i *size + col] / scale;
            inv[i * size + col] = inv[i * size + col] / scale;
        }
        if (i < size - 1)
        {
            for (int row = i + 1; row < size; row++)
            {
                double factor = input_matrix[row * size + i];
                for (int col = 0; col < size; col++)
                {
                    input_matrix[row * size + col] -= factor * input_matrix[i * size + col];
                    inv[row * size + col] -= factor * inv[i * size + col];
                }
            }
        }
    }

    for (int zeroing_col = size - 1; zeroing_col >= 1; zeroing_col--)
    {
        for (int row = zeroing_col - 1; row >= 0; row--)
        {
            double factor = input_matrix[row * size + zeroing_col];
            for (int col = 0; col < size; col++)
            {
                input_matrix[row * size + col] -= factor * input_matrix[zeroing_col * size + col];
                inv[row * size + col] -= factor * inv[zeroing_col * size + col];
            }
        }
    }

    free(input_matrix);
}

/*
    Function that performs matrix vector multiplication
    and stores the result in the res vector passed as an argument.
*/
void matmul(double *mat, double *vec, double *res, int D)
{
    for (int i = 0; i < D; i++)
    {
        res[i] = 0;
        for (int j = 0; j < D; j++)
            res[i] += mat[i * D + j] * (double)vec[j];
    }
}

/*
    Function that calculates the dot product between two vectors
    and returns the results.
*/
double dotProduct(double *a, double *b, int D)
{
    double result = 0.0;
    for (int i = 0; i < D; i++)
        result += a[i] * b[i];
    return result;
}

/*
    Function that performs z-score normalization on the training examples.
*/
void standardize(double *data, int row_per_process, int world_size, int D)
{
    // Calculate the mean for each dimension
    double *local_mean = calloc(D, sizeof(double));
    for (int j = 0; j < D; j++)
    {
        local_mean[j] = 0.0;
        for (int i = 0; i < row_per_process; i++)
            local_mean[j] += data[i * D + j];
        local_mean[j] /= row_per_process;
    }

    double *global_mean = calloc(D, sizeof(double));

    MPI_Allreduce(local_mean, global_mean, D, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < D; i++)
        global_mean[i] /= world_size;

    // Calculate the standard deviation for each dimension
    double *local_stdDev = calloc(D, sizeof(double));
    for (int j = 0; j < D; j++)
    {
        local_stdDev[j] = 0.0;
        for (int i = 0; i < row_per_process; i++)
            local_stdDev[j] += pow(data[i * D + j] - global_mean[j], 2);
        local_stdDev[j] = sqrt(local_stdDev[j] / (row_per_process - 1));
    }

    double *global_stdDev = calloc(D, sizeof(double));

    MPI_Allreduce(local_stdDev, global_stdDev, D, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    for (int i = 0; i < D; i++)
        global_stdDev[i] /= world_size;

    // Perform standardization
    for (int i = 0; i < row_per_process; i++)
        for (int j = 0; j < D; j++)
            data[i * D + j] = (data[i * D + j] - global_mean[j]) / global_stdDev[j];

    free(local_mean);
    free(global_mean);
    free(local_stdDev);
    free(global_stdDev);
}
