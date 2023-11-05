#ifndef EM_PROJECT_E_STEP_PARALLEL
#define EM_PROJECT_E_STEP_PARALLEL

// run expectation step
void e_step(float **X, float **mean, float ***cov, float *weights, float **p_val);

#endif 
