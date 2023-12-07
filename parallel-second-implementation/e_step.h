#ifndef EM_PROJECT_E_STEP_DYNAMIC_PARALLEL
#define EM_PROJECT_E_STEP_DYNAMIC_PARALLEL

#include "constants.h"

// computes pdf
double gaussian(Sample x, double *mean, double *cov, int j);

// run expectation step
void e_step(Sample *samples, double *mean, double *cov, double *weights, double *p_val, int row_per_process);

#endif 
