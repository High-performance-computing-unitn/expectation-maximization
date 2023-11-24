#ifndef EM_PROJECT_EM_ALGORITHM_DYNAMIC_PARALLEL
#define EM_PROJECT_EM_ALGORITHM_DYNAMIC_PARALLEL

#include "constants.h"

void em_train(Sample *Samples, float *mean, float *cov, float *weights, float *p_val, int process_samples, int process_rank);
void initialize(float *mean, float *cov, float *weights);

#endif
