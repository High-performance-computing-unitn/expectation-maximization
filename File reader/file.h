#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../constants.h"


int readFile(char* rows[MAX_LEN])
{
    FILE *file = fopen(filePath, "r");

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
        return rowN;
    }
}

/*
FILE *file = fopen(filePath, "r");

if (file != NULL)
{
    int line = 0;

    while (!feof(file) && !ferror(file))
    {
        if (fgets(rows, MAX_LEN, file) != NULL)
        {
            //printf("Row: %s", rows);
            line++;
        }
    }

    fclose(file);
    return line;

}*/