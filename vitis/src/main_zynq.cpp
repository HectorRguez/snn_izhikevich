#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "network_func.h"
#include "aux_func.h"
#include "../../../snn_config/network.h" // Network coefficients [AUTO GENERATED]
#include "../../../snn_config/snn_defs.h" // Common definitions
#include "data.h"    // Testing data [AUTO GENERATED]

// HW drivers
#include "./hw/snn_izikevich_hw_zynq.h"

// Optget externs (avoid squiggly lines)
extern char* optarg;
extern int optopt;

// Simulation defines
const float train_data_proportion = 0.7;
const int n_steps = 30;

// Time libraries
#include "xtime_l.h"

#define COUNTS_PER_MS	(COUNTS_PER_SECOND/1000)
XTime clk_start, clk_end, clk_duration = 0;
void start_clock() { XTime_GetTime(&clk_start); }
void stop_clock()  { XTime_GetTime(&clk_end); clk_duration += (clk_end - clk_start); }

void reset_clock() { clk_duration = 0; }
float get_clock_ms()  { return (1.0 * clk_duration) / COUNTS_PER_MS; }


int main(int argc, char *argv[]){
    // Dynamically allocated memory
    bool* out_spk = NULL;                      // Network output
    // Print data and network (if verbose)
    // ============================================================
    if(true)
    { 
        // Print the normalized input file
        printf("\nNORMALIZED DATA\n");
        for(int i = 0; i < n_data; i++){
            printf("%3i: ", i);
            for(int j = 0; j < n_parameters-1; j++){
                printf("%5.3f ", data[i*n_parameters + j]);
            }
            printf("%3i", labels[i]);
            printf("\n");
        }
        printf("\n\n");

        // Print the weights and biases
        printf("WEIGHTS\n");
        for(int i = 0; i < n_weights; i++){
            printf("%5.3f ", weights[i]);
        }
        printf("\n\n");
        printf("BIASES\n");
        for(int i = 0; i < n_biases; i++){
            printf("%5.3f ", biases[i]);
        }
        printf("\n\n");
    }

    // Test the network in SW
    // ============================================================
    printf("Executing the network in SW.\n");
	int total = 0, correct = 0;
    int start_test_idx = (int)(train_data_proportion*n_data);
    out_spk = (bool*)malloc(n_outputs*n_steps*sizeof(bool));
    
	
	reset_clock();
    start_clock();
    for(int i = start_test_idx; i < n_data; i++){
        // Execute network
        float* in_c = &data[i*n_parameters];
        forward_network_izhi(in_c, n_inputs, n_outputs, out_spk, 
            n_per_layer, n_layers, weights, biases);
        // Check results
        int result = rate_code_result(out_spk, n_outputs, n_steps);
        if(result == labels[i]) correct++;
        total++;
    }
    stop_clock();

    printf("NETWORK EXECUTION RESULTS:\n");
    float percentage = ((float)correct)/((float)total) * 100.0; 
    printf("Correctly classified %i/%i flowers (%5.2f%%)", 
        correct, total, percentage);
    printf("\n");
    printf("Total execution time:\t\t%.2f ms.\n", get_clock_ms());

	free(out_spk);

    // Test the network in HW
    // ============================================================
    printf("Executing the network in HW.\n");
	int total = 0, correct = 0;
    int start_test_idx = (int)(train_data_proportion*n_data);
    out_spk = (bool*)malloc(n_outputs*n_steps*sizeof(bool));


    reset_clock();
    start_clock();
    for(int i = start_test_idx; i < n_data; i++){
        // Set up network accelerator
        float* in_c = &data[i*n_parameters];
        hw_snn_izikevich_config_network(in_c, n_inputs, n_outputs, n_per_layer, n_layers);

        // Run network accelerator
        hw_snn_izikevich_run(weights, n_weights, biases, n_biases, n_inputs, n_outputs, n_per_layer, n_layers, out_spk);

        // Check results
        int result = rate_code_result(out_spk, n_outputs, n_steps);
        if(result == labels[i]) correct++;
        total++;
    }
    stop_clock();

	free(out_spk);

    printf("NETWORK EXECUTION RESULTS:\n");
    float percentage = ((float)correct)/((float)total) * 100.0; 
    printf("Correctly classified %i/%i flowers (%5.2f%%)", 
        correct, total, percentage);
    printf("\n");
    printf("Total execution time:\t\t%.2f ms.\n", get_clock_ms());
}