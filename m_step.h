#ifndef EM_PROJECT_M_STEP_H
#define EM_PROJECT_M_STEP_H

#include "constants.h"


void calc_sum_pij(float p_val[N][K], float res[K]);

void calc_covariance_nom(float X[N][D], float mean[K][D], float cov[K][D][D], float p_val[N][K]);

void m_step_covariance(float cov[K][D][D], float sum_pij[K]);

void calc_mean_nom(float X[N][D], float p_val[N][K], float res[K][D]);

void m_step_mean(float mean[K][D], float mean_nom[K][D], float sum_pij[K]);

void m_step_weights(float sum_pij[K], float weights[K]);

void m_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]);

#endif //EM_PROJECT_M_STEP_H
