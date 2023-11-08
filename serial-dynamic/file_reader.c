#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"


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

int readFile(char *rows[MAX_ROW_LEN])
{
    FILE *file = fopen(FILE_PATH, "r");

    if (file != NULL)
    {
        int rowN = 0;
        char line[1024];

        // get number of gaussians from the first line
        if (fgets(line, 1024, file))
        {
//            K = atoi(strdup(line));
        }

        // get all the other lines of the dataset
        while (fgets(line, 1024, file))
        {
            rows[rowN] = strdup(line);
            rowN++;
        }

        fclose(file);
        return rowN;
    }
}

void fill_matrix(float* mat, int N, int D) {
    char *rows[MAX_ROW_LEN];
    int n = readFile(rows);
    for (int row = 0; row < N; row++)
    {
        int col = 0;
        // pointer to the first element
        char *ptr = strtok(rows[row], ",");
        while (ptr != NULL)
        {
            if (ptr != ",")
            {
                // convert element to double and store it in the matrix
                mat[row * D + col] = strtof(ptr, NULL);
                ptr = strtok(NULL, ",");
                col++;
            }
        }
    }
}
