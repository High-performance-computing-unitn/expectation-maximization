#ifndef EM_PROJECT_M_STEP_DYNAMIC_PARALLEL
#define EM_PROJECT_M_STEP_DYNAMIC_PARALLEL

#include "constants.h"

// run maximization step
void m_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]);

#endif 
