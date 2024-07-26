#include "xil_printf.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "network_func.h"
#include "aux_func.h"
#include "network.h" // Network coefficients [AUTO GENERATED]
#include "snn_defs.h" // Common definitions
#include "data.h"    // Testing data [AUTO GENERATED]
 
// HW drivers
#include "./hw/snn_izikevich_hw_zynq.h"
 
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

    // Normalize data (if needed)
    int error = normalize_data(data, n_data, n_parameters);
    if(error < 0){
        xil_printf("ERROR while normalizing data.\n");
        return (-1);
    }

    // Test the network in SW
    // ============================================================
    xil_printf("============================================\r\n");
    xil_printf("                 SW Network.\r\n");
    xil_printf("============================================\r\n");
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

        xil_printf("%i. %i %i\n\r", i, labels[i], result);
    }
    stop_clock();

    float percentage = ((float)correct)/((float)total) * 100.0; 
    xil_printf("Correctly classified %i/%i flowers (%i%%)", 
        correct, total, (int)percentage);
    xil_printf("\r\n");
    xil_printf("Total execution time: %i ms.\r\n", (int)get_clock_ms());

	free(out_spk);

    // Test the network in HW
    // ============================================================
    xil_printf("============================================\r\n");
    xil_printf("                 HW network.\r\n");
    xil_printf("============================================\r\n"); 

    if (hw_setup() != XST_SUCCESS) {
		xil_printf("Error initializing hardware blocks...\r\n");
		return -1;
	}

	total = 0, correct = 0;
    start_test_idx = (int)(train_data_proportion*n_data);
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

    xil_printf("NETWORK EXECUTION RESULTS:\r\n");
    percentage = ((float)correct)/((float)total) * 100.0; 
    xil_printf("Correctly classified %i/%i flowers (%5.2f%%)", 
        correct, total, percentage);
    xil_printf("\r\n");
    xil_printf("Total execution time: %i ms.\r\n", (int)get_clock_ms());
    
    return 0;
}