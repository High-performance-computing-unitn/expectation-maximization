#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    Function that reads values from the input file and stores them in the rows array
*/
void readFile(char *rows[MAX_LINES], char *FILE_PATH)
{
    FILE *file = fopen(FILE_PATH, "r");

    if (file != NULL)
    {
        int rowN = 0;
        char line[MAX_ROW_LEN];

        // get all the lines of the file and store them in the rows array
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
    Function that populates the matrix by parsing values in each row
*/
void fill_matrix(double *mat, int N, int D, char *FILE_PATH)
{
    char *rows[MAX_LINES];
    readFile(rows, FILE_PATH);
    int col = 0;
    char delim[] = ",";
    for (int row = 0; row < N; row++)
    {
        char *ptr = strtok(rows[row], delim); // pointer to the first element
        while (ptr != NULL)
        {
            if (ptr != delim)
            {
                mat[row * D + col] = strtof(ptr, NULL); // convert element to double and store it in the matrix
                ptr = strtok(NULL, delim); // update pointer to next element
                col++;
            }
        }
        col = 0;
    }
}