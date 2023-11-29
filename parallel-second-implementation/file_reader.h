#ifndef EM_PROJECT_READER_DYNAMIC_PARALLEL
#define EM_PROJECT_READER_DYNAMIC_PARALLEL

#include "constants.h"

// populate the matrix of samples
void fill_matrix(Sample *samples, char **rows, int process_samples, int process_rank, char *FILE_PATH);

#endif 