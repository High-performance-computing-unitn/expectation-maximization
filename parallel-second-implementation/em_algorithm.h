#ifndef EM_PROJECT_EM_ALGORITHM_DYNAMIC_PARALLEL
#define EM_PROJECT_EM_ALGORITHM_DYNAMIC_PARALLEL

#include "constants.h"

// em algorithm
void em_train(Sample *samples, float *mean, float *cov, float *weights, float *p_val, int process_samples, int process_rank);

// initialize mean, cov and weights 
void initialize(float *mean, float *cov, float *weights);

#endif
