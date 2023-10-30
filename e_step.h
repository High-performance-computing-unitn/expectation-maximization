#ifndef EM_PROJECT_E_STEP_H
#define EM_PROJECT_E_STEP_H

#include "constants.h"

// run expectation step
void e_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]);

#endif //EM_PROJECT_E_STEP_H
