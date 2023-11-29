#ifndef EM_PROJECT_E_STEP_SERIAL
#define EM_PROJECT_E_STEP_SERIAL

// returns the gaussian probability density estimate
float gaussian(float *x, float *mean, float *cov, int D);

// copy values of mean and covariance
void get_cluster_mean_cov(float *mean, float *cov, float *m_res, float *cov_res, int k, int D);

// run expectation step
void e_step(float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D);

#endif 
