#ifndef EM_PROJECT_EM_ALGORITHM_PARALLEL
#define EM_PROJECT_EM_ALGORITHM_PARALLEL

// initialize initial values of mean, covariance and weights
void initialize(float *mean, float *cov, float *weights, int K, int D);

// run expectation-maximization algorithm
void em_train(int n_iter, float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D);

#endif 
