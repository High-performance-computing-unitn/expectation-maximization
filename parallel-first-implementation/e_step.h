#ifndef EM_PROJECT_E_STEP_H
#define EM_PROJECT_E_STEP_H

// run expectation step
void e_step(float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D);

float gaussian(float *x, float *mean, float *cov, int D);

#endif //EM_PROJECT_E_STEP_H
