#ifndef EM_PROJECT_EM_ALGORITHM_DYNAMIC_PARALLEL
#define EM_PROJECT_EM_ALGORITHM_DYNAMIC_PARALLEL

#include "constants.h"

// em algorithm
void em_train(Sample *samples, double *mean, double *cov, double *weights, double *p_val, int process_samples, int process_rank);

// initialize mean, cov and weights 
void initialize(double *mean, double *cov, double *weights);

#endif
