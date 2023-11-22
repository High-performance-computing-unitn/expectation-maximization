#ifndef EM_PROJECT_M_STEP_DYNAMIC_PARALLEL
#define EM_PROJECT_M_STEP_DYNAMIC_PARALLEL

#include "constants.h"

// run maximization step
void m_step_parallel(float **local_p_val, Sample *samples, float **mean, float ***cov, float *weights, int process_rank, int process_samples);

#endif 
