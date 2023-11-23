#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

/*
https://github.com/Presto412/Parallel-Matrix-Inversion-with-OpenMP/blob/master/pdc-da2-inverse-gje.cpp
*/

void getCofactor(float *A, float *temp, int p, int q, int n)
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
                temp[i * (n - 1) + j] = A[row * n + col];
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

float determinant(float *A, int n)
{
    float det = 0;

    // Base case: if the matrix contains a single element
    if (n == 1)
        return A[0];

    float *temp = (float *)malloc(n * n * sizeof(float));

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

// void getCofactor(float **A, float **temp, int p, int q, int n)
// {
//     int i = 0, j = 0;

//     // Looping for each element of the matrix
//     for (int row = 0; row < n; row++)
//     {
//         for (int col = 0; col < n; col++)
//         {
//             //  Copying into temporary matrix only those
//             //  element which are not in given row and
//             //  column
//             if (row != p && col != q)
//             {
//                 temp[i][j++] = A[row][col];

//                 // Row is filled, so increase row index and
//                 // reset col index
//                 if (j == n - 1)
//                 {
//                     j = 0;
//                     i++;
//                 }
//             }
//         }
//     }
// }

// float determinant(float **input_matrix, int n, int size) // Recursive function for finding determinant of matrix.
// {
//     float det = 0; // Initialize result

//     //  Base case : if matrix contains single element
//     if (n == 1)
//         return input_matrix[0][0];

//     float **temp = (float **)malloc(size * sizeof(float *)); // To store cofactors
//     for (int i = 0; i < size; i++)
//         temp[i] = (float *)malloc(size * sizeof(float));

//     int sign = 1; // To store sign multiplier

//     // Iterate for each element of first row
//     for (int f = 0; f < n; f++)
//     {
//         // Getting Cofactor of A[0][f]
//         getCofactor(input_matrix, temp, 0, f, n);
//         det += sign * input_matrix[0][f] * determinant(temp, n - 1, size);

//         // terms are to be added with alternate sign
//         sign = -sign;
//     }

//     for (int i = 0; i < size; i++)
//     {
//         free(temp[i]);
//     }
//     free(temp);

//     return det;
// }

// void adjoint(float **input_matrix, float **adj, int size) // Function to get adjoint of A[N][N] in adj[N][N].
// {
//     if (size == 1)
//     {
//         adj[0][0] = 1;
//         return;
//     }

//     // temp is used to store cofactors of A[][]
//     int sign = 1;
//     float **temp = (float **)malloc(size * sizeof(float *));
//     for (int i = 0; i < size; i++)
//         temp[i] = (float *)malloc(size * sizeof(float));

//     for (int i = 0; i < size; i++)
//     {
//         for (int j = 0; j < size; j++)
//         {
//             // Get cofactor of A[i][j]
//             getCofactor(input_matrix, temp, i, j, size);

//             // sign of adj[j][i] positive if sum of row
//             // and column indexes is even.
//             sign = ((i + j) % 2 == 0) ? 1 : -1;

//             // Interchanging rows and columns to get the
//             // transpose of the cofactor matrix
//             adj[j][i] = (sign) * (determinant(temp, size - 1, size));
//         }
//     }

//     for (int i = 0; i < size; i++)
//     {
//         free(temp[i]);
//     }
//     free(temp);
// }

// float **inverse(float **input_matrix, int size) // Function to calculate and store inverse
// {
//     float **I = (float **)malloc(size * sizeof(float *));
//     for (int i = 0; i < size; i++)
//         I[i] = (float *)malloc(size * sizeof(float));

//     // Find determinant of A[][]
//     float det = determinant(input_matrix, size, size);

//     float **adj = (float **)malloc(size * sizeof(float *)); // Find adjoint
//     for (int i = 0; i < size; i++)
//         adj[i] = (float *)malloc(size * sizeof(float));

//     adjoint(input_matrix, adj, size);

//     // Find Inverse using formula "inverse(A) =
//     // adj(A)/det(A)"
//     for (int i = 0; i < size; i++)
//         for (int j = 0; j < size; j++)
//             I[i][j] = adj[i][j] / det;

//     for (int i = 0; i < size; i++)
//     {
//         free(adj[i]);
//     }
//     free(adj);

//     return I;
// }

/*
END O CODE
*/

float **generate_identity(int size)
{
    float **I = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        I[i] = (float *)malloc(size * sizeof(float));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                I[i][j] = 1;
            }
            else
            {
                I[i][j] = 0;
            }
        }
    }
    return I;
}

float **generate_inverse_parallel(float **input_matrix, int threads, int size)
{
    float **I = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        I[i] = (float *)malloc(size * sizeof(float));

    I = generate_identity(size);

    for (int i = 0; i < size; i++)
    {
        if (input_matrix[i][i] == 0)
        {
            // swap nearest subsequent row s.t input_matrix[i][i] != 0 after swapping
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
        omp_set_num_threads(threads);
#pragma omp parallel for
        for (int col = 0; col < size; col++)
        {
            input_matrix[i][col] = input_matrix[i][col] / scale;
            I[i][col] = I[i][col] / scale;
        }
        if (i < size - 1)
        {
#pragma omp parallel for
            for (int row = i + 1; row < size; row++)
            {
                float factor = input_matrix[row][i];
                for (int col = 0; col < size; col++)
                {
                    input_matrix[row][col] -= factor * input_matrix[i][col];
                    I[row][col] -= factor * I[i][col];
                }
            }
        }
    }
    for (int zeroing_col = size - 1; zeroing_col >= 1; zeroing_col--)
    {
#pragma omp parallel for
        for (int row = zeroing_col - 1; row >= 0; row--)
        {
            float factor = input_matrix[row][zeroing_col];
            for (int col = 0; col < size; col++)
            {
                input_matrix[row][col] -= factor * input_matrix[zeroing_col][col];
                I[row][col] -= factor * I[zeroing_col][col];
            }
        }
    }
    return I;
}

float **generate_inverse_serial(float **input_matrix, int size)
{
    int i = 0;
    float **I = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        I[i] = (float *)malloc(size * sizeof(float));

    I = generate_identity(size);
    for (i = 0; i < size; i++)
    {
        if (input_matrix[i][i] == 0)
        {
            // swap nearest subsequent row s.t input_matrix[i][i] != 0 after swapping
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
            I[i][col] = I[i][col] / scale;
        }
        if (i < size - 1)
        {
            for (int row = i + 1; row < size; row++)
            {
                float factor = input_matrix[row][i];
                for (int col = 0; col < size; col++)
                {
                    input_matrix[row][col] -= factor * input_matrix[i][col];
                    I[row][col] -= factor * I[i][col];
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
                I[row][col] -= factor * I[zeroing_col][col];
            }
        }
    }
    return I;
}

void print_matrix(float **matrix, int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("\n");
        for (int j = 0; j < SIZE; j++)
        {
            printf("%f ", matrix[i][j]);
        }
    }
    printf("\n");
}

float determinantOfMatrix(float **mat, int n)
{
    int index; // Initialize result
    float det = 1, num1, num2, total = 1;

    // temporary array for storing row
    float temp[n + 1];

    // loop for traversing the diagonal elements
    for (int i = 0; i < n; i++)
    {
        index = i; // initialize the index

        // finding the index which has non zero value
        while (index < n && mat[index][i] == 0)
        {
            index++;
        }
        if (index == n) // if there is non zero element
        {
            // the determinant of matrix as zero
            continue;
        }
        if (index != i)
        {
            // loop for swapping the diagonal element row and
            // index row
            for (int j = 0; j < n; j++)
            {
                float tmp = mat[index][j];
                mat[index][j] = mat[i][j];
                mat[i][j] = tmp;
            }
            // determinant sign changes when we shift rows go through determinant properties
            det = det * pow(-1, index - i);
        }

        // storing the values of diagonal row elements
        for (int j = 0; j < n; j++)
        {
            temp[j] = mat[i][j];
        }
        // traversing every row below the diagonal element
        for (int j = i + 1; j < n; j++)
        {
            num1 = temp[i];   // value of diagonal element
            num2 = mat[j][i]; // value of next row element

            // traversing every column of row
            // and multiplying to every row
            for (int k = 0; k < n; k++)
            {
                // multiplying to make the diagonal
                // element and next row element equal
                mat[j][k] = (num1 * mat[j][k]) - (num2 * temp[k]);
            }
            total = total * num1; // Det(kA)=kDet(A);
        }
    }

    // multiplying the diagonal elements to get determinant
    for (int i = 0; i < n; i++)
    {
        det = det * mat[i][i];
    }
    return (det / total); // Det(kA)/k=Det(A);
}

float chatdet(float **matrix, int size) {
    float det = 0;
    int sign = 1;

    if (size == 1) {
        return matrix[0][0];
    }

    // Create temporary matrix for submatrix
    float **temp = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        temp[i] = (float *)malloc(size * sizeof(float));

    // Decompose the matrix into smaller matrices and compute their determinants
    #pragma omp parallel for private(temp) reduction(+:det)
    for (int i = 0; i < size; i++) {
        int subi = 0; // Submatrix row index

        // Create the submatrix
        for (int row = 1; row < size; row++) {
            int subj = 0; // Submatrix column index

            for (int col = 0; col < size; col++) {
                if (col != i) {
                    temp[subi][subj++] = matrix[row][col];
                }
            }
            subi++;
        }

        // Calculate the determinant recursively for the submatrix
        det += sign * matrix[0][i] * chatdet(temp, size);

        // Alternate the sign for next iteration
        sign = -sign;
    }

    for (int i = 0; i < size; i++)
    {
        free(temp[i]);
    }
    free(temp);
    
    return det;
}


int main()
{
    srand(time(NULL));
    int SIZE = 9;
    int threads = 2;
    clock_t start = clock();
    clock_t end = clock();

    printf("SIZE of matrix is: %d -- threads: %d\n", SIZE, threads);

    float **matrix1 = (float **)malloc(SIZE * sizeof(float *));
    for (int i = 0; i < SIZE; i++)
        matrix1[i] = (float *)malloc(SIZE * sizeof(float));

    float **matrix3 = (float **)malloc(SIZE * sizeof(float *));
    for (int i = 0; i < SIZE; i++)
        matrix3[i] = (float *)malloc(SIZE * sizeof(float));

    float *matrix2 = (float *)malloc(SIZE * SIZE * sizeof(float));

    float *matrix4 = (float *)malloc(SIZE * SIZE * sizeof(float));

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrix1[i][j] = (float)rand() / (float)(RAND_MAX / SIZE);
            matrix2[i * SIZE + j] = matrix1[i][j];
            matrix4[i * SIZE + j] = matrix1[i][j];
            matrix3[i][j] = matrix1[i][j];
        }
    }

    printf("Input Matrix is:");
    print_matrix(matrix1, SIZE);

    
    start = clock();

    float det3;
    #pragma omp parallel
    {
        #pragma omp single
        {
            det3 = chatdet(matrix1, SIZE);
        }
    }
    
    end = clock();
    printf("\nDeterminant chatgpt took: %f seconds and resulted in: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC, det3);

 

    start = clock();

    float det = determinant(matrix2, SIZE);
    
    end = clock();
    printf("\nDeterminant took: %f seconds and resulted in: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC, det);

    start = clock();

    float det2;

#pragma omp parallel if (omp_in_parallel())
    {
        det2 = determinant(matrix4, SIZE);
    }

    end = clock();
    printf("\nDeterminant O mode took: %f seconds and resulted in: %f", (double)(end - start) / CLOCKS_PER_SEC, det2);

    for (int i = 0; i < SIZE; i++)
    {
        free(matrix1[i]);
        free(matrix3[i]);
    }
    free(matrix1);
    free(matrix2);
    free(matrix3);
    free(matrix4);

    return 0;
}

/*
   srand(time(NULL));
    int SIZE = 3;
    int threads = 2;
    clock_t start = clock();
    clock_t end = clock();

    printf("SIZE of matrix is: %d -- threads: %d\n", SIZE, threads);

    float **matrix1 = (float **)malloc(SIZE * sizeof(float *));
    for (int i = 0; i < SIZE; i++)
        matrix1[i] = (float *)malloc(SIZE * sizeof(float));

    float **matrix2 = (float **)malloc(SIZE * sizeof(float *));
    for (int i = 0; i < SIZE; i++)
        matrix2[i] = (float *)malloc(SIZE * sizeof(float));

    float **matrix3 = (float **)malloc(SIZE * sizeof(float *));
    for (int i = 0; i < SIZE; i++)
        matrix3[i] = (float *)malloc(SIZE * sizeof(float));

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrix1[i][j] = (float)rand() / (float)(RAND_MAX / SIZE);
            matrix2[i][j] = matrix1[i][j];
            matrix3[i][j] = matrix1[i][j];
        }
    }

    printf("Input Matrix is:");
    print_matrix(matrix1, SIZE);



    float **matrix_parallel = (float **)malloc(SIZE * sizeof(float *));
    for (int i = 0; i < SIZE; i++)
        matrix_parallel[i] = (float *)malloc(SIZE * sizeof(float));

    start = clock();
    //matrix_parallel = generate_inverse_parallel(matrix2, threads, SIZE);

    //determinant parallel



    end = clock();
    printf("\nParallel inverse took: %f seconds and resulted in:", (double)(end - start) / CLOCKS_PER_SEC);
    //print_matrix(matrix_parallel, SIZE);

    for (int i = 0; i < SIZE; i++)
    {
        free(matrix2[i]);
        free(matrix_parallel[i]);
    }
    free(matrix2);
    free(matrix_parallel);


    // float **matrix_parallel_O = (float **)malloc(SIZE * sizeof(float *));
    // for (int i = 0; i < SIZE; i++)
    //     matrix_parallel_O[i] = (float *)malloc(SIZE * sizeof(float));

    // start = clock();
    // matrix_parallel_O = inverse(matrix3, SIZE);
    // end = clock();
    // printf("\nParallel inverse O mode took: %f seconds and resulted in:", (double)(end - start) / CLOCKS_PER_SEC);
    // print_matrix(matrix_parallel_O, SIZE);

    // for (int i = 0; i < SIZE; i++)
    // {
    //     free(matrix3[i]);
    //     free(matrix_parallel_O[i]);
    // }
    // free(matrix3);
    // free(matrix_parallel_O);

    float **matrix_serial = (float **)malloc(SIZE * sizeof(float *));
    for (int i = 0; i < SIZE; i++)
        matrix_serial[i] = (float *)malloc(SIZE * sizeof(float));

    start = clock();
    //matrix_serial = generate_inverse_serial(matrix1, SIZE);

    //determinant serial


    determinantOfMatrix(matrix1, SIZE);

    end = clock();
    printf("\nSerial inverse took: %f seconds and resulted in:", (double)(end - start) / CLOCKS_PER_SEC);
    //print_matrix(matrix_serial, SIZE);

    for (int i = 0; i < SIZE; i++)
    {
        free(matrix1[i]);
        free(matrix_serial[i]);
    }
    free(matrix1);
    free(matrix_serial);
    */