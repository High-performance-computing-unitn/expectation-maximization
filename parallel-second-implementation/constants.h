#ifndef EM_PROJECT_CONSTANTS_DYNAMIC_PARALLEL
#define EM_PROJECT_CONSTANTS_DYNAMIC_PARALLEL

#define MAX_LINES 1000000 // maximum number of rows in the file
#define MAX_ROW_LEN 1000 // maximum length of rows in the file
#define PI 3.14159265358979323846
#define MASTER_PROCESS 0 // master process

extern int D; // dimension of a feature
extern int N; // number of training examples
extern int K; // number of Gaussians
extern int max_iter; // number of iterations
extern int last_process; // process with higher ID
extern char log_filepath[1024]; // log likelihood file path

typedef struct Sample{ // struct for each element of the input file, each element has an array of its dimensions
    float *dimensions;
}Sample;

#endif 