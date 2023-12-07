#include <math.h>
#include <stdlib.h>
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
            #pragma omp parallel for
            for (int i = 0; i < n2; i++)
                matrix[i] = m[i];

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
        return (m[0] * (m[4] * m[8] - m[5] * m[7])
                - m[1] * (m[3] * m[8] - m[5] * m[6])
                + m[2] * (m[3] * m[7] - m[4] * m[6]));
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

// double determinant(double *A, int n)
// {
//     double det = 0;

//     // Base case: if the matrix contains a single element
//     if (n == 1)
//         return A[0];

//     double *temp = (double *)calloc(n * n, sizeof(double));

//     int sign = 1;

//     for (int f = 0; f < n; f++)
//     {
//         // Getting the cofactor of A[0][f]
//         getCofactor(A, temp, 0, f, n);
//         det += sign * A[f] * determinant(temp, n - 1);

//         // Terms are to be added with alternate sign
//         sign = -sign;
//     }

//     free(temp);

//     return det;
// }

void adjoint(double *A, double *adj, int n)
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
            getCofactor(A, temp, i, j, n);

            // Sign of adj[j][i] is positive if the sum of row and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchange rows and columns to get the transpose of the cofactor matrix
            adj[j * n + i] = (sign) * (determinant(temp, n - 1));
        }
    }

    free(temp);
}

void inverse(double *A, double *inv, double *det, int n)
{
    // Find the determinant of A[][]
    *det = determinant(A, n);

    // Find the adjoint
    double *adj = (double *)calloc(n * n, sizeof(double));
    adjoint(A, adj, n);

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

    double * global_stdDev = calloc(D, sizeof(double));

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
