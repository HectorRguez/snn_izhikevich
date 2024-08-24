// Standard libraries
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Custom libraries
#include "snn_defs.h"       // Common definitions
#include "network_func.h"   // Network execution in SW
#include "aux_func.h"       // Auxiliary functions
#include "network.h"        // Network coefficients [AUTO GENERATED]
#include "data.h"           // Testing data [AUTO GENERATED]
 
// Network execution in HW
#include "./hw/snn_izhikevich_hw_zynq.h"

// PYNQ libraries
#include "xil_printf.h"

int main(int argc, char *argv[]){
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

    // SW Testing
    {
		int total = 0, correct = 0;
		int start_test_idx = (int)(TRAIN_DATA_PROPORTION*n_data);
		bool out_spk[MAX_LAYER_SIZE*NUM_STEPS] = {0};
		reset_clock();
		start_clock();
		for(int i = start_test_idx; i < n_data; i++){
			// Execute network
			float* in_c = &data[i*n_parameters];
			forward_network(in_c, n_inputs, out_spk,
				n_per_layer, n_layers, weights, biases, NEURON_MODEL);
			// Check results
			int result = rate_code_result(out_spk, n_outputs, NUM_STEPS);
			if(result == labels[i]) correct++;
			total++;
		}
		stop_clock();

		// Compute accuracy and print execution time
		float percentage = ((float)correct)/((float)total) * 100.0;
		xil_printf("Correctly classified %i/%i (%i%%)",
			correct, total, (int)percentage);
		xil_printf("\r\n");
		float run_time = get_clock_ms();
		int run_time_ms = (int)run_time;
		int run_time_cent_ms = (int)((float) run_time *100.0) % 100;
		xil_printf("Total execution time: %i.%i ms.\r\n", run_time_ms, run_time_cent_ms);
    }
    // Test the network in HW
    // ============================================================
    xil_printf("============================================\r\n");
    xil_printf("                 HW network.\r\n");
    xil_printf("============================================\r\n");

    // HW Testing
    {
    	// Ensure that the HW has been correctly initialized
    	if (hw_setup() != XST_SUCCESS) {
    			xil_printf("Error initializing hardware blocks...\r\n");
    			return -1;
		}

        // Prepare network input stream
        uint64_t input_stream [AXI_PORTS][TRANSMISSION_SIZE*MAX_LAYER_COUNT/2] = {0};
        uint32_t n_input_stream = hw_snn_izikevich_prepare_weight_bias_stream(weights, n_weights, biases,  n_biases,
            n_inputs, n_per_layer, n_layers, input_stream);

    	int total = 0, correct = 0;
		int start_test_idx = (int)(TRAIN_DATA_PROPORTION*n_data);
		bool out_spk[MAX_LAYER_SIZE*NUM_STEPS] = {0};

		reset_clock();
		start_clock();
		for(int i = start_test_idx; i < n_data; i++){
			// Set up network accelerator
			float* in_c = &data[i*n_parameters];
			hw_snn_izikevich_config_network(in_c, n_inputs, n_outputs, n_per_layer, n_layers);

			// Run network accelerator
			hw_snn_izikevich_run(input_stream, n_input_stream, n_outputs, out_spk);

			// Check results
			int result = rate_code_result(out_spk, n_outputs, NUM_STEPS);
			if(result == labels[i]) correct++;
			total++;
		}
		stop_clock();

		// Compute accuracy and print execution time
		float percentage = ((float)correct)/((float)total) * 100.0;
		xil_printf("Correctly classified %i/%i (%i%%)",
			correct, total, (int)percentage);
		xil_printf("\r\n");
		float run_time = get_clock_ms();
		int run_time_ms = (int)run_time;
		int run_time_cent_ms = (int)((float) run_time *100.0) % 100;
		xil_printf("Total execution time: %i.%i ms.\r\n", run_time_ms, run_time_cent_ms);

    }
    return 0;
}
