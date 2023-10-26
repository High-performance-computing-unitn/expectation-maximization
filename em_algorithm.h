#ifndef EM_PROJECT_EM_ALGORITHM_H
#define EM_PROJECT_EM_ALGORITHM_H

#include "constants.h"

void initialize(float mean[K][D], float cov[K][D][D], float weights[K]);

void em_train(int n_iter, float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]);

#endif //EM_PROJECT_EM_ALGORITHM_H
