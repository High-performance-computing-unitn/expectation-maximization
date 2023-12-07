#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

/*
    Strdup implementation
*/
char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if (dup)
        strcpy(dup, str);
    return dup;
}

/*
    Function that reads from the input file and store each row in the rows array.
*/
void readFile(char *rows[MAX_LINES], char *FILE_PATH)
{
    FILE *file = fopen(FILE_PATH, "r");

    if (file != NULL)
    {
        int rowN = 0;
        char line[MAX_ROW_LEN];

        // get all the lines of the dataset
        while (fgets(line, MAX_ROW_LEN, file))
        {
            rows[rowN] = strdup(line);
            rowN++;
        }

        fclose(file);
    }
    else
    {
        printf("Error opening the input file!");
        exit(1);
    }
}

/*
    Function that fill the matrix of samples by parsing the input rows.
*/
void fill_matrix(double *mat, int N, int D, char *FILE_PATH)
{
    char *rows[MAX_LINES];
    readFile(rows, FILE_PATH);
    int col = 0;
    char delim[] = ","; // delimiter of columns
    for (int row = 0; row < N; row++) // iterate rows
    {
        char *ptr = strtok(rows[row], delim); // pointer to the first element
        while (ptr != NULL)
        {
            if (ptr != delim)
            {
                mat[row * D + col] = strtod(ptr, NULL); // convert element to double and store it in the matrix
                ptr = strtok(NULL, delim);
                col++;
            }
        }
        col = 0;
    }
}
