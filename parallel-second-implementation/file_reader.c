#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

int N, D, K;

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

void read_file(char **rows, int process_samples, int process_rank, char *FILE_PATH)
{
    int start = process_samples * process_rank;
    int end = start + process_samples - 1;

    FILE *file = fopen(FILE_PATH, "r");
    if (file != NULL)
    {
        char row[MAX_ROW_LEN];
        int count = 0;
        int rowN = 0;

        if (process_rank == last_process) // if the last process is reading it reads untile eof to avoid leaving samples behind
        {
            while (fgets(row, MAX_ROW_LEN, file) != NULL)
            {
                if (count >= start)
                {
                    rows[rowN] = strdup(row);
                    rowN++;
                }
                count++;
            }
        }
        else
        {
            while (fgets(row, MAX_ROW_LEN, file) != NULL) // if another process is reading it reads only its data
            {
                if (count >= start && count <= end)
                {
                    rows[rowN] = strdup(row);
                    rowN++;
                }
                count++;
            }
        }
        fclose(file);
    }
    else
    {
        printf("Cannot open file!");
        exit(1);
    }
}

void fill_matrix(Sample *dataset, char **rows, int process_samples, int process_rank, char *FILE_PATH)
{
    read_file(rows, process_samples, process_rank, FILE_PATH);

    // fills the matrix with the values of each element in each row converting it to double
    for (int row = 0; row < process_samples; row++)
    {
        int col = 0;
        char delim[] = ",";                                // delimiter of columns
        char *ptr = strtok(rows[row], delim);              // pointer to the first element
        Sample s;                                          // current sample
        s.dimensions = (float *)malloc(D * sizeof(float)); // allocate dimensions array of sample
        while (ptr != NULL)
        {
            if (ptr != delim)
            {
                s.dimensions[col] = strtof(ptr, NULL); // convert element to float and store it in the sample
                ptr = strtok(NULL, delim);             // shift the pointer
                col++;
            }
        }
        dataset[row] = s; // store the sample
    }
}