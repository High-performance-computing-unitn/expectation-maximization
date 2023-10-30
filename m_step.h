#ifndef EM_PROJECT_M_STEP_H
#define EM_PROJECT_M_STEP_H

#include "constants.h"

// run maximization step
void m_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]);

#endif //EM_PROJECT_M_STEP_H
