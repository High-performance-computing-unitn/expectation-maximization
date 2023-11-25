#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

/*
https://matematicamente.it/forum/viewtopic.php?f=15&t=145130
*/

double my_abs(double const a)
{
    return (a < 0.)? -a : a;
}

double matrix_det(double const m[], uint32_t const n);

double factorize (double m[], uint32_t const n);

// Funzioni per inizializzare la matrice
void set_matrix(double m[], uint32_t const n);
void set2identity(double m[], uint32_t const n);

int main()
{
    uint32_t const MatDim = 20;
    uint32_t const MatSize = MatDim * MatDim;
    clock_t start, end;

    double * matrix = calloc(MatSize, sizeof(double));

    if(matrix)
    {
        set_matrix(matrix, MatDim);
        //set2identity(matrix, MatDim);

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
        

        start = clock();
        double const det = matrix_det(matrix, MatDim);

        end = clock();
        printf("\nDeterminant took: %f seconds and resulted in: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC, det);

        free(matrix);
    }
    else
    {
        perror("calloc() :");
    }
}


void set_matrix(double m[], uint32_t const n)
{
    uint32_t const n2 = n*n;
    #pragma omp parallel for
    for (uint32_t i = 0; i < n2; ++i)
        m[i] = (float)rand() / (float)(RAND_MAX / n);
}


void set2identity(double m[], uint32_t const n)
{
    uint32_t const n2 = n*n;
    #pragma omp parallel for
    for (uint32_t i = 0; i < n2; i+=(n+1))
        m[i] = 1.;
}


double matrix_det(double const m[], uint32_t const n)
{
    if(n>3)
    {
        uint32_t const n2 = n*n;
        double * matrix = calloc(n2, sizeof(double));
        if(matrix)
        {
            // copia della matrice per non sovrascriverla
            #pragma omp parallel for
            for (uint32_t i = 0; i < n2; ++i)
                matrix[i] = m[i];

            double det = factorize(matrix, n);

            if(det != 0)
            {
                #pragma omp parallel for reduction(*:det)
                for (uint32_t i = 0; i < n; ++i)
                {
                    uint32_t const ind = i * n + i;
                    double value = matrix[ ind ];
                    det *= value;
                }
            }

            free(matrix);
            return det;
        }
        else
        {
            perror("calloc() :");
            return 0.;
        }
    }
    else if(n==3)
    {
        return (  m[0]*(m[4] * m[8] - m[5] * m[7])
                  - m[1]*(m[3] * m[8] - m[5] * m[6])
                  + m[2]*(m[3] * m[7] - m[4] * m[6]) );
    }
    else if(n == 2)
    {
        return (m[0] * m[3] - m[1] * m[2]);
    }
    else if(n == 1)
    {
        return m[0];
    }
    else return 0.;
}



double factorize (double m[], uint32_t const n)
{
    double parity = 1.;

    for( uint32_t k = 0; k < n-1; ++k )
    {
        // ricerca massimo
        double max = my_abs( m[k*n + k] );
        uint32_t ip = k;
        for(uint32_t i = k+1; i < n; ++i)
        {
            double const t = my_abs( m[i*n + k] );
            if(t > max)
            {
                max = t;
                ip = i;
            }
        }

        if(max == 0.)
        {
            return 0.;
        }

        if(ip != k)
        {
            parity *= -1;
            #pragma omp parallel for
            for(uint32_t i = 0; i < n; ++i)
            {
                double const t = m[k*n + i];
                m[k*n + i] = m[ip*n + i];
                m[ip*n + i] = t;
            }
        }

        double const pe = m[k * n + k];
        #pragma omp parallel for
        for(uint32_t i = k+1; i < n; ++i)
            m[i*n + k] /= pe;

        #pragma omp parallel for
        for(uint32_t i = k+1; i < n; ++i)
        {
            double const mik = m[i*n + k];
            for(uint32_t j = k+1; j<n; ++j)
            {
                m[i*n + j] -= mik * m[k*n + j];
            }
        }
    }

    return parity;
}