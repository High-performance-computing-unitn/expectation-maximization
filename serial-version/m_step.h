#ifndef EM_PROJECT_M_STEP_SERIAL
#define EM_PROJECT_M_STEP_SERIAL

// run maximization step
void m_step(double *X, double *mean, double *cov, double *weights, double *p_val, int K, int N, int D);

#endif 
