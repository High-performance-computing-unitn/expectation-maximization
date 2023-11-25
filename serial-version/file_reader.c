#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"

char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if (dup)
    {
        strcpy(dup, str);
    }
    return dup;
}

void readFile(char *rows[MAX_ROW_LEN], char *FILE_PATH)
{
    FILE *file = fopen(FILE_PATH, "r");

    if (file != NULL)
    {
        int rowN = 0;
        char line[1024];

        // get all the other lines of the dataset
        while (fgets(line, 1024, file))
        {
            rows[rowN] = strdup(line);
            rowN++;
        }

        fclose(file);
    }
    else
    {
        printf("The file does not exist!");
        exit(0);
    }
}

void fill_matrix(float *mat, int N, int D, char *FILE_PATH)
{
    char *rows[MAX_ROW_LEN];
    readFile(rows, FILE_PATH);
    for (int row = 0; row < N; row++)
    {
        int col = 0;
        // pointer to the first element
        char delim[] = ","; // delimiter of columns
        char *ptr = strtok(rows[row], delim);
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
