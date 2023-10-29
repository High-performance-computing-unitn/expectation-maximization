#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../constants.h"

int K; // number of Gaussians

int readFile(char *rows[MAX_LEN])
{
    FILE *file = fopen(filePath, "r");

    if (file != NULL)
    {
        int rowN = 0;
        char line[1024];

        // get number of gaussians from the first line
        if (fgets(line, 1024, file))
        {
            K = atoi(strdup(line));
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