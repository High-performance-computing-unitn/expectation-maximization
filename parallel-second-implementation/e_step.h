#ifndef EM_PROJECT_E_STEP_DYNAMIC_PARALLEL
#define EM_PROJECT_E_STEP_DYNAMIC_PARALLEL

#include "constants.h"

float gaussian(Sample x, float *mean, float *cov, int j);

// run expectation step
void e_step(Sample *samples, float *mean, float *cov, float *weights, float *p_val, int row_per_process);

#endif 
