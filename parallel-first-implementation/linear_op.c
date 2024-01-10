#include <math.h>
#include <stdlib.h>

/*
 * Code for matrix inverse taken from
 * https://www.geeksforgeeks.org/adjoint-inverse-matrix/
 */

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

double determinant(double *A, int n)
{
    double det = 0;

    // Base case: if the matrix contains a single element
    if (n == 1)
        return A[0];

    double *temp = (double *)calloc(n * n, sizeof(double));

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        // Getting the cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        det += sign * A[f] * determinant(temp, n - 1);

        // Terms are to be added with alternate sign
        sign = -sign;
    }

    free(temp);

    return det;
}

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
void standardize(double *data, int N, int D)
{
    // Calculate the mean for each dimension
    double *mean = calloc(D, sizeof(double));
    for (int j = 0; j < D; j++)
    {
        mean[j] = 0.0;
        for (int i = 0; i < N; i++)
            mean[j] += data[i * D + j];
        mean[j] /= N;
    }

    // Calculate the standard deviation for each dimension
    double *stdDev = calloc(D, sizeof(double));
    for (int j = 0; j < D; j++)
    {
        stdDev[j] = 0.0;
        for (int i = 0; i < N; i++)
            stdDev[j] += pow(data[i * D + j] - mean[j], 2);
        stdDev[j] = sqrt(stdDev[j] / (N - 1));
    }

    // Perform standardization
    for (int i = 0; i < N; i++)
        for (int j = 0; j < D; j++)
            data[i * D + j] = (data[i * D + j] - mean[j]) / stdDev[j];

    free(mean);
    free(stdDev);
}
