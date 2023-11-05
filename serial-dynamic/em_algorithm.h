#ifndef EM_PROJECT_EM_ALGORITHM_PARELLEL
#define EM_PROJECT_EM_ALGORITHM_PARALLEL

// initialize initial values of mean, covariance and weights
void initialize(float **mean, float ***cov, float *weights);

// run expectation-maximization algorithm
void em_train(int n_iter, float **X, float **mean, float ***cov, float *weights, float **p_val);

#endif 
