#ifndef EM_PROJECT_M_STEP_PARALLEL
#define EM_PROJECT_M_STEP_PARALLEL

// run maximization step
void m_step(float **X, float **mean, float ***cov, float *weights, float **p_val);

#endif 
