#ifndef EM_PROJECT_E_STEP_DYNAMIC_PARALLEL
#define EM_PROJECT_E_STEP_DYNAMIC_PARALLEL

#include "constants.h"

// run expectation step
void e_step(Sample *X, float **mean, float ***cov, float *weights, float **p_val, int row_per_process);

#endif 
