#ifndef EM_PROJECT_READER_DYNAMIC_PARALLEL
#define EM_PROJECT_READER_DYNAMIC_PARALLEL

#include "constants.h"

void fill_matrix(Sample *dataset, char **rows, int process_samples, int process_rank);

#endif 