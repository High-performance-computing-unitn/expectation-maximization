#include <stdlib.h>


void get_cluster_mean_cov(float *mean, float *cov, float *m_res, float *cov_res, int k, int D) {
    int start_ind = k * D * D;
    for (int r = 0; r < D; r++) {
        for (int d = 0; d < D; d ++) {
            cov_res[r * D + d] = cov[start_ind + r * D + d];
        }
    }

    for (int d = 0; d < D; d ++) {
        m_res[d] = mean[k * D + d];
    }
}


void divide_rows(int* data_count, int* data_displ, int* p_count, int* p_displ,
                 int N, int D, int K, int comm_sz) {
    for (int i = 0; i < comm_sz; i++) {
        data_count[i] = N / comm_sz;
        if (i < N % comm_sz) {
            data_count[i]++;
        }
    }

    data_displ[0] = 0;
    for (int i = 1; i < comm_sz; i++) {
        data_displ[i] = data_displ[i-1] + data_count[i-1];
    }

    for (int i = 0; i < comm_sz; i++) {
        p_count[i] = data_count[i] * K;
        p_displ[i] = data_displ[i] * K;

        data_count[i] *= D;
        data_displ[i] *= D;
    }
}


void free_em_data(float *X, float *mean, float *cov, float *weights, float *p_val) {
    free(X);
    free(weights);
    free(mean);
    free(cov);
    free(p_val);
}


void free_rows_data(int* data_count, int* data_displ, int* p_count, int* p_displ) {
    free(data_count);
    free(data_displ);
    free(p_count);
    free(p_displ);
}

