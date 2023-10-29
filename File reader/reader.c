#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "../constants.h"

int D; // dimension of a feature
int N; // number of training examples

int getDimensions(char *row, const char delim)
{
	// starts from one because it counts commas, not elements
	int dimensions = 1;
	char *tmp = row;
	char *last_comma = 0;

	while (*tmp)
	{
		if (delim == *tmp)
		{
			dimensions++;
			last_comma = tmp;
		}
		tmp++;
	}
	return dimensions;
}

int main()
{
	// contains the rows of the csv file
	char *rows[MAX_LEN];

	// number of rows aka samples
	N = readFile(rows);

	// number of dimensions of each point
	D = getDimensions(rows[0], ',');

	// matrix of the points
	double dataset[N][D];
	
	// fills the matrix with the values of each element in each row converting it to double
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
				dataset[row][col] = strtod(ptr, NULL);
				ptr = strtok(NULL, ",");
				col++;
			}
		}
	}

	return 0;
}

/*
	// print the matrix
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < D; j++)
		{
			printf("%f ", dataset[i][j]);
		}
		printf("\n");
	}
*/