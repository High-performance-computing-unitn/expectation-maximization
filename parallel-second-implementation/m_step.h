#ifndef EM_PROJECT_M_STEP_DYNAMIC_PARALLEL
#define EM_PROJECT_M_STEP_DYNAMIC_PARALLEL

#include "constants.h"

// run maximization step
void m_step_parallel(double *local_p_val, Sample *samples, double *mean, double *cov, double *weights, int process_rank, int process_samples);

#endif 
