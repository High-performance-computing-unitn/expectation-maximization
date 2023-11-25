#ifndef EM_PROJECT_M_STEP_SERIAL
#define EM_PROJECT_M_STEP_SERIAL

// run maximization step
void m_step(float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D);

#endif 
