#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"

char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if (dup)
        strcpy(dup, str);

    return dup;
}

void readFile(char *rows[MAX_LEN], char *FILE_PATH)
{
    FILE *file = fopen(FILE_PATH, "r");

    if (file != NULL)
    {
        int rowN = 0;
        char line[1024];

        while (fgets(line, 1024, file))
        {
            rows[rowN] = strdup(line);
            rowN++;
        }

        fclose(file);
    }
    else
    {
        printf("Error opening file!");
        exit(1);
    }
}

void fill_matrix(float *mat, int N, int D, char *FILE_PATH)
{
    char *rows[MAX_LEN];
    readFile(rows, FILE_PATH);
    for (int row = 0; row < N; row++)
    {
        int col = 0;
        char delim[] = ",";
        char *ptr = strtok(rows[row], delim); // pointer to the first element
        while (ptr != NULL)
        {
            if (ptr != delim)
            {
                // convert element to double and store it in the matrix
                mat[row * D + col] = strtof(ptr, NULL);
                ptr = strtok(NULL, delim);
                col++;
            }
        }
    }
}