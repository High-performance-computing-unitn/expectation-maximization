#ifndef EM_PROJECT_CONSTANTS_DYNAMIC_PARALLEL
#define EM_PROJECT_CONSTANTS_DYNAMIC_PARALLEL

#define FILE_PATH "./data/smallDataset.csv" // file to be read
#define MAX_LINES 1000000 // maximum number of rows in the file
#define MAX_ROW_LEN 1000 // maximum length of rows in the file
#define PI 3.14159265358979323846
#define MASTER_PROCESS 0

extern int D; // dimension of a feature
extern int N; // number of training examples
extern int K; // number of Gaussians
extern int max_iter; // number of iterations
extern int last_process; // process with higher ID

typedef struct Sample{
    float *dimensions;
}Sample;

#endif 