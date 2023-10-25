#include "constants.h"
#include "m_step.h"
#include "e_step.h"


void em_train(int n_iter, float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]) {
    for (int i = 0; i < n_iter; i++) {
        m_step(X, mean, cov, weights, p_val);
        e_step(X, mean, cov, weights, p_val);
    }
}
