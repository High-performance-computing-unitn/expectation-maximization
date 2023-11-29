#ifndef EM_PROJECT_M_STEP_H
#define EM_PROJECT_M_STEP_H

// run maximization step
void m_step(float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D);

void m_step_parallel(float *local_p_val, float *local_examples, float *mean,
                     float *cov, float *weights, int my_rank, int row_per_process, int K, int D);

#endif //EM_PROJECT_M_STEP_H
