#ifndef EM_PROJECT_M_STEP_H
#define EM_PROJECT_M_STEP_H

// run maximization step
void m_step(double *X, double *mean, double *cov, double *weights, double *p_val, int K, int N, int D);

void m_step_parallel(double *local_p_val, double *local_examples, double *mean,
                     double *cov, double *weights, int my_rank, int row_per_process, int K, int D);

#endif //EM_PROJECT_M_STEP_H
