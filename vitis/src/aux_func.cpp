#include "aux_func.h"


int count_n_biases(int*n_per_layer, int n_layers){
    int n_biases = 0;
    for(int i = 0; i < n_layers; i++){
        n_biases += n_per_layer[i];
    }
    return n_biases;
}

int count_n_weights(int n_in, int*n_per_layer, int n_layers){
    // Parse the weights
    int n_weights = 0, current_layer_n = 0, prev_layer_n = n_in;
    for(int i = 0; i < n_layers; i++){
        current_layer_n = n_per_layer[i];
        n_weights += current_layer_n * prev_layer_n;
        prev_layer_n = current_layer_n; // Next iteration
    }
    return n_weights;
}


int normalize_data(float buffer[], int n_lines, int n_parameters){
    float min, max, curr, curr_norm; 
    for(int i = 0; i < n_parameters; i++){  // Last parameter -> Label
        // Find the minimum and maximum value
        min = buffer[i], max = buffer[i];
        for(int j = 1; j < n_lines; j++){
            curr = buffer[j*n_parameters+i];
            min = (curr < min) ? curr : min;
            max = (curr > max) ? curr : max;
        }
        if(max == min) return -1; // Avoid division by zero error

        // Normalize
        for(int j = 0; j < n_lines; j++){
            curr = buffer[j*n_parameters+i];
            curr_norm = (curr - min) / (max - min);
            buffer[j*n_parameters+i] = curr_norm;
        }
    }
    return 0;
}

void parse_in_out(float buffer[MAX_N_INPUTS*MAX_N_INPUT_VALUES], 
    float*in, int*out, int n_lines, int n_parameters){

    int buffer_idx = 0;
    for(int i = 0; i < n_lines; i++){
        for(int j = 0; j < n_parameters-1; j++){ // Last parameter -> Label
            in[i*n_parameters+j] = buffer[buffer_idx++];
        }
        out[i] = (int)buffer[buffer_idx++];
    }
}

int rate_code_result(bool*out_spk, uint32_t n_out, uint32_t n_steps){
    // Count the number of spikes on each output neuron
    int* absolute_freq = (int*)calloc(n_out, sizeof(int));
    for(uint32_t i = 0; i < n_out; i++){
        for(int j = 0; j < n_steps; j++){
            if(out_spk[i*n_steps+j]) absolute_freq[i]++;
        }
    }

    // Count the maximum number of spikes
    uint32_t max_freq = 0, max_freq_idx = 0;
    for(uint32_t i = 0; i < n_out; i++){
        if(absolute_freq[i] > max_freq){
            max_freq = absolute_freq[i];
            max_freq_idx = i;
        }
    }
    free(absolute_freq);

    return (max_freq_idx); 
}