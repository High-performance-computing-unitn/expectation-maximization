#ifndef EM_PROJECT_READER_H
#define EM_PROJECT_READER_H

// populate the matrix of samples
void parallel_fill_matrix(double *mat, int N, int D, int rank, int row_per_process, int comm_sz, char *FILE_PATH);

#endif //EM_PROJECT_READER_H
