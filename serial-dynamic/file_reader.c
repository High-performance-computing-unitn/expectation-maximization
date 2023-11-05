#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "file_reader.h"

int N, D, K;

int get_dimensions(char *row, const char delim)
{
    int dimensions = 1; // starts from one because it counts commas, not elements
    char*tmp = row;

    while (*tmp)
    {
        if (delim == *tmp)
        {
            dimensions++;
        }
        tmp++;
    }
    return dimensions;
}

void read_file(char **rows)
{
    FILE *file = fopen(FILE_PATH, "r");

    if (file != NULL)
    {
        char row[MAX_ROW_LEN];

        K = atoi(fgets(row, MAX_ROW_LEN, file));

        int rowN = 0;
        do
        {
            fgets(row, MAX_ROW_LEN, file);
            rows[rowN] = strndup(row, MAX_ROW_LEN);
            rowN++;
        } while (!feof(file));

        N = rowN - 1;
        D = get_dimensions(rows[0], ',');
        fclose(file);
    }
    else
    {
        printf("Error opening file");
        exit(0);
    }
}

void fill_matrix(char **rows, float **dataset)
{
    // fills the matrix with the values of each element in each row converting it to double
    for (int row = 0; row < N; row++)
    {
        int col = 0;
        char delim[] = ",";
        // pointer to the first element
        char *ptr = strtok(rows[row], delim);
        while (ptr != NULL)
        {
            if (ptr != delim)
            {
                // convert element to double and store it in the matrix
                dataset[row][col] = strtof(ptr, NULL);
                ptr = strtok(NULL, delim);
                col++;
            }
        }
    }
}
