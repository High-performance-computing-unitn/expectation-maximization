#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "../constants.h"

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
	int samples = readFile(rows);

	// number of dimensions of each point
	int dimensions = getDimensions(rows[0], ',');

	// matrix of the points
	double dataset[samples][dimensions];

	// delimiter of each element
	char delim[] = ",";

	// fills the matrix with the values of each element in each row converting it to double
	for (int row = 0; row < samples; row++)
	{
		int col = 0;
		char *ptr = strtok(rows[row], delim);
		while (ptr != NULL)
		{
			if (ptr != delim)
			{
				dataset[row][col] = strtod(ptr, NULL);
				ptr = strtok(NULL, delim);
				col++;
			}
		}
	}

	// print the matrix
	for (int i = 0; i < samples; i++)
	{
		for (int j = 0; j < dimensions; j++)
		{
			printf("%f ", dataset[i][j]);
		}
		printf("\n");
	}

	return 0;
}