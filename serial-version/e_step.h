#ifndef EM_PROJECT_E_STEP_SERIAL
#define EM_PROJECT_E_STEP_SERIAL

// run expectation step
void e_step(float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D);

#endif 
