#ifndef EM_PROJECT_EM_ALGORITHM_SERIAL
#define EM_PROJECT_EM_ALGORITHM_SERIAL

// initialize initial values of mean, covariance and weights
void initialize(double *mean, double *cov, double *weights, int K, int D);

// run expectation-maximization algorithm
void em_train(int n_iter, double *X, double *mean, double *cov, double *weights, double *p_val, int K, int N, int D);

#endif 
