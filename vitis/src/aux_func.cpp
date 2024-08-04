#include "aux_func.h"

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


int rate_code_result(bool*out_spk, uint32_t n_out, uint32_t n_steps){
    // Count the number of spikes on each output neuron
    int* absolute_freq = (int*)calloc(n_out, sizeof(int));
    for(uint32_t i = 0; i < n_out; i++){
        for(int j = 0; j < n_steps; j++){
            if(out_spk[i*n_steps+j]) absolute_freq[i]++;
        } 
    }

    // Count the maximum number of spikes
    int max_freq = 0, max_freq_idx = 0;
    for(uint32_t i = 0; i < n_out; i++){
        if(absolute_freq[i] > max_freq){
            max_freq = absolute_freq[i];
            max_freq_idx = i;
        }
    }
    free(absolute_freq);

    return (max_freq_idx); 
}

// Time measuring functions
XTime clk_start, clk_end, clk_duration = 0;
void start_clock(){ 
    XTime_GetTime(&clk_start); 

}

void stop_clock(){
    XTime_GetTime(&clk_end); clk_duration += (clk_end - clk_start); 

}

void reset_clock(){
    clk_duration = 0;
}

float get_clock_ms(){
    return (1.0 * clk_duration) / COUNTS_PER_MS;
}