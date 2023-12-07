#ifndef EM_PROJECT_E_STEP_H
#define EM_PROJECT_E_STEP_H

// run expectation step
void e_step(double *X, double *mean, double *cov, double *weights, double *p_val, int K, int N, int D);

// computes pdf
double gaussian(double *x, double *mean, double *cov, int D);

#endif //EM_PROJECT_E_STEP_H
