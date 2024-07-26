#ifndef _AUX_FUN_H_
#define _AUX_FUN_H_

// Includes
#include <stdbool.h>
#include <stdlib.h>

// Data size defines
#define NET_BUFFER_SIZE 1000
#define MAX_LINE_SIZE 100
#define MAX_N_INPUTS 1000
#define MAX_N_INPUT_VALUES 10
#define PATH_SIZE 100

// Function prototypes
int read_bin(char file_name[PATH_SIZE], int buffer[NET_BUFFER_SIZE]);
int count_n_biases(int*n_per_layer, int n_layers);
int count_n_weights(int n_in, int*n_per_layer, int n_layers);
int read_csv(char file_name[PATH_SIZE], 
    float buffer[MAX_N_INPUTS*MAX_N_INPUT_VALUES], 
    int*n_lines, int*n_parameters);
int normalize_data(float buffer[], int n_lines, int n_parameters);
void parse_in_out(float buffer[MAX_N_INPUTS*MAX_N_INPUT_VALUES], 
    float*in, int*out, int n_lines, int n_parameters);
int rate_code_result(bool*out_spk, int n_out, int n_steps);

#endif /* _AUX_FUN_H_ */