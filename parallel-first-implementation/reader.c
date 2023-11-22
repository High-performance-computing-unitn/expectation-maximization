#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"

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
    return 0;
}


void fill_matrix(float* mat, int N, int D) {
    char *rows[MAX_LEN];
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

//int getDimensions(char *row, const char delim)
//{
//    // starts from one because it counts commas, not elements
//    int dimensions = 1;
//    char *tmp = row;
//    char *last_comma = 0;
//
//    while (*tmp)
//    {
//        if (delim == *tmp)
//        {
//            dimensions++;
//            last_comma = tmp;
//        }
//        tmp++;
//    }
//    return dimensions;
//}

//int main()
//{
//	// contains the rows of the csv file
//	char *rows[MAX_LEN];
//
//	// number of rows aka samples
//	N = readFile(rows);
//
//	// number of dimensions of each point
//	D = getDimensions(rows[0], ',');
//
//	// matrix of the points
//	double dataset[N][D];
//
//	// fills the matrix with the values of each element in each row converting it to double
//	for (int row = 0; row < N; row++)
//	{
//		int col = 0;
//		// pointer to the first element
//		char *ptr = strtok(rows[row], ",");
//		while (ptr != NULL)
//		{
//			if (ptr != ",")
//			{
//				// convert element to double and store it in the matrix
//				dataset[row][col] = strtod(ptr, NULL);
//				ptr = strtok(NULL, ",");
//				col++;
//			}
//		}
//	}
//
//	return 0;
//}
