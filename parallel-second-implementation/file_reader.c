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
void readFile(char *rows[MAX_LINES], int rank, int row_per_process, int comm_sz, char *FILE_PATH)
{
    // each process computes its starting and ending index
    int start_index = row_per_process * rank;
    int end_index = start_index + row_per_process - 1;

    FILE *file = fopen(FILE_PATH, "r");

    if (file != NULL)
    {
        int rowN = 0;
        int count = 0;
        char line[MAX_ROW_LEN];

        // last process reads all the remaining lines
        if(rank == comm_sz - 1){
            // get all the lines of the file
            while (fgets(line, MAX_ROW_LEN, file) != NULL)
            {
                if (count >= start_index)
                {
                    rows[rowN] = strdup(line);
                    rowN++;
                }
                count++;
            }
        }
        else
        {
            while (fgets(line, MAX_ROW_LEN, file) != NULL) // if another process is reading it reads only its data
            {
                if (count >= start_index && count <= end_index) // if the row is between start and end index the process reads it
                {
                    rows[rowN] = strdup(line);
                    rowN++;
                }
                count++;
            }
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
void parallel_fill_matrix(double *mat, int N, int D, int rank, int row_per_process, int comm_sz, char *FILE_PATH)
{
    char *rows[MAX_LINES];
    // each process reads the file
    readFile(rows, rank, row_per_process, comm_sz, FILE_PATH);

    int col = 0;
    char delim[] = ",";
    for (int row = 0; row < row_per_process; row++)
    {
        char *ptr = strtok(rows[row], delim); // pointer to the first element
        while (ptr != NULL)
        {
            if (ptr != delim)
            {
                mat[row * D + col] = strtod(ptr, NULL); // convert element to double and store it in the matrix
                ptr = strtok(NULL, delim); // update pointer to next element
                col++;
            }
        }
        col = 0;
    }
}