#ifndef EM_PROJECT_E_STEP_SERIAL
#define EM_PROJECT_E_STEP_SERIAL

// returns the gaussian probability density estimate
double gaussian(double *x, double *mean, double *cov, int D);

// copy values of mean and covariance
void get_cluster_mean_cov(double *mean, double *cov, double *m_res, double *cov_res, int k, int D);

// run expectation step
void e_step(double *X, double *mean, double *cov, double *weights, double *p_val, int K, int N, int D);

#endif 
