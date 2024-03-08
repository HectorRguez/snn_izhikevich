#ifndef _START_H_
#define _START_H_

// Common libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "snn_results.h"
#include "snn_network_defs.h"

// Hardware libraries
#include "hw/zynq/platform.h"
#include "hw/snn_izikevich_hw_zynq.h"

// Time libraries
#include "xtime_l.h"

#define COUNTS_PER_MS	(COUNTS_PER_SECOND/1000)
XTime clk_start, clk_end, clk_duration = 0;
void start_clock() { XTime_GetTime(&clk_start); }
void stop_clock()  { XTime_GetTime(&clk_end); clk_duration += (clk_end - clk_start); }

void reset_clock() { clk_duration = 0; }
float get_clock_ms()  { return (1.0 * clk_duration) / COUNTS_PER_MS; }

int run_network();
int run_hw_network();
void get_inputs(int32_t t);
void init_network(uint8_t change_neuron_types, uint8_t feedback);
#ifdef PERSIST_RESULTS
void persist_results(uint64_t *out_stream);
#endif

// Global variables: network and results
static bool	neuron_type[NUMBER_OF_LAYERS][NEURONS_PER_LAYER];
static float	synapse_weights[NUMBER_OF_NEURONS][NEURONS_PER_LAYER];
static uint32_t 	p_hw[AXI_INPUT_LENGTH];
static uint64_t 	network_stream[AXI_NEURON_TYPE_LENGTH];
static uint64_t 	weights_stream[AXI_WEIGHTS_PORTS][AXI_WEIGHTS_LENGTH];
static uint64_t 	output_stream[AXI_OUTPUT_LENGTH];
static uint64_t		out_hw[RUN_STEPS * AXI_OUTPUT_LENGTH];

// Include application
#include "snn_network_xor.h"

int start() {
	init_platform();
    run_network();
    cleanup_platform();
    return 0;
}

int run_network() {
	srand(1);

	printf("\n\n");
	printf("*****************************************************\n");
	printf("*              Neural Network Simulation            *\n");
	printf("*****************************************************\n");
	printf("Neurons per layer = %d\n", NEURONS_PER_LAYER);
	printf("Number of layers = %d\n", NUMBER_OF_LAYERS);
	printf("Number of neurons = %d (%.1fK)\n", NUMBER_OF_NEURONS, ((float)NUMBER_OF_NEURONS)/1000);
	printf("Number of synapses = %d (%.1fM)\n", NUMBER_OF_SYNAPSES, ((float)NUMBER_OF_SYNAPSES)/1000000);

	printf("Initializing network...\n");
	init_network(1, 0);
	generate_inputs();

	printf("*****************************************************\n");
	printf("*                 Running HW version                *\n");
	printf("*****************************************************\n");

	if (run_hw_network() != 0)
		return -1;

  	// Sends the neuron firings via serial and network performance
	#ifdef PERSIST_RESULTS
		printf("*****************************************************\n");
		printf("*                Persisting HW results              *\n");
		printf("*****************************************************\n");
  		persist_hw_results(neuron_type[0], out_hw);
		persist_app_results();
	#endif

  	printf("**************** Simulation finished ****************\n");
	return 0;
}

/*****************************************************************************
 *                        Network (Hardware version)    	                 *
 *****************************************************************************/

int run_hw_network() {

	int32_t t, o_off;

	// Setting up FPGA block
	printf("Initializing hardware blocks...\n");
	if (hw_setup() != XST_SUCCESS) {
		printf("Error initializing hardware blocks...\n");
		return -1;
	}
	printf("Hardware blocks initialized successfully\n");

	// Send network to FPGA
  	printf("Sending network configuration to FPGA...\n");
  	reset_clock();
  	start_clock();
  	if (hw_snn_izikevich_config_network(network_stream, (uint64_t *)output_stream) != XST_SUCCESS) {
		printf("Error executing hardware block with 'hw_snn_izikevich_config_network'...\n");
		return -1;
	}
  	stop_clock();
  	printf("Network sent successfully in %.2f ms.\n", get_clock_ms());

  	// Flush inputs array's cache
  	for (uint32_t i = 0; i < AXI_WEIGHTS_PORTS; i++)
  		Xil_DCacheFlushRange((uint32_t)weights_stream[i], AXI_WEIGHTS_LENGTH * sizeof(uint64_t));

  	// Simulate for a period of time
  	printf("Starting %ld steps...\n", RUN_STEPS);
  	reset_clock();
  	for (t = 0, o_off = 0; t < RUN_STEPS; t++, o_off += AXI_OUTPUT_LENGTH) {

  		// Compute/get inputs at specified time
  		get_inputs(t);

		// Calculate the spikes in the network for this time step
		start_clock();
		if (hw_snn_izikevich_run_step(p_hw, weights_stream, (uint64_t *)&out_hw[o_off]) != XST_SUCCESS) {
			printf("Error executing hardware block with 'hw_snn_izikevich_run_step'...\n");
			return -1;
		}
		stop_clock();

		// Feedback if training mode enabled
		#ifdef NUM_TRAINING_TRIALS
		if ((t % TRIAL_TIME_MS) == (TRIAL_TIME_MS - 1)) {
			feedback_error(t);
			// Update weights
			init_network(0, 1);
		}
		#endif
  	}
  	printf("=> Results\n");
  	printf("Network  time:\t%.2f ms.\n", (float)RUNTIME_MS);
  	printf("Total execution time:\t\t%.2f ms.\n", get_clock_ms());
  	printf("Execution time per second:\t%.2f ms.\n", get_clock_ms()/((float)RUNTIME_MS/1000));
  	return 0;
}

/*****************************************************************************
 *                         Network Initialization    	                     *
 *****************************************************************************/
void get_inputs(int32_t t) {
	int32_t x;

	int32_t stream_id, bit;
	stream_id = 0; bit = 0;
	uint32_t converter;
	
	// Possion distribution of firing inputs
	for (x = 0; x < INPUT_SYNAPSES; x++) {
		if(bit == 0) converter = 0;

		uint8_t spiked = get_spike(t, x);
		if (spiked) {
			converter |= (uint32_t)1 << bit;
		}

		// AXI-Lite words are 32-bit
		if (++bit == AXIL_SIZE) { p_hw[stream_id++] = converter; bit = 0; }
	}
	if(bit > 0) p_hw[stream_id++] = converter;
}

void init_network(uint8_t change_neuron_types, uint8_t feedback) {
	int32_t x, y, l, xl;
	int32_t stream_id, bit;
	stream_id = 0; bit = 0;
	uint64_t converter;

	// Set neuron types
	for (l = 0; l < NUMBER_OF_LAYERS; l++) for (xl = 0; xl < NEURONS_PER_LAYER; xl++) {
		if (change_neuron_types == 1) // Get neuron type if requested, otherwise use the old one
			neuron_type[l][xl] = get_neuron_type(l, xl);

		if (bit == 0) { converter = 0; }
		if (neuron_type[l][xl])
		{
			converter |= (uint64_t)1 << bit;
		}
		if (++bit == AXI_SIZE) { network_stream[stream_id++] = converter; bit = 0; }
	}
	if (bit != 0) { network_stream[stream_id++] = converter; bit = 0; }

	uint32_t stream_fifo = 0; stream_id = 0; bit = 0;

	// Set input weights
	for (x = 0; x < NEURONS_PER_LAYER; x++) {
		for (y = 0; y < NEURONS_PER_LAYER; y++) {
			float weight = get_weight(0, x, x, y, feedback);

			synapse_weights[x][y] = weight;

			#if PRECISION_TYPE == FIXED_POINT
			// TODO
			#elif PRECISION_TYPE == FLOATING_POINT
			uint32_t* weight_ptr = (uint32_t*)&weight;
			converter |= (uint64_t)*weight_ptr << bit;
			#endif

			bit += WEIGHT_BITS;
			if (bit == AXI_SIZE) {
				weights_stream[stream_fifo++][stream_id] = converter;
				if (stream_fifo == AXI_WEIGHTS_PORTS) {stream_fifo = 0; stream_id ++; }
				bit = 0; converter = 0;
			}
		}
		if (bit > 0 || stream_fifo > 0) {
			if (bit > 0) weights_stream[stream_fifo++][stream_id] = converter;
			while(stream_fifo < AXI_WEIGHTS_PORTS) { weights_stream[stream_fifo++][stream_id] = 0; }
			stream_id++;
		}
		bit = 0; converter = 0; stream_fifo = 0;
	}

	// Set weights between layers
	x = NEURONS_PER_LAYER;
	for (l = 1; l < NUMBER_OF_LAYERS; l++) for (xl = 0; xl < NEURONS_PER_LAYER; xl++, x++) {
		for (y = 0; y < NEURONS_PER_LAYER; y++) {
			float weight = get_weight(l, xl, x, y, feedback);
			synapse_weights[x][y] = weight;

			#if PRECISION_TYPE == FIXED_POINT
			// TODO
			#elif PRECISION_TYPE == FLOATING_POINT
			uint32_t* weight_ptr = (uint32_t*)&weight;
			converter |= (uint64_t)*weight_ptr << bit;
			#endif

			bit += WEIGHT_BITS;
			if (bit == AXI_SIZE) {

				#if PRECISION_TYPE == FIXED_POINT
				// TODO
				#elif PRECISION_TYPE == FLOATING_POINT
				weights_stream[stream_fifo++][stream_id] = converter;
				#endif

				if (stream_fifo == AXI_WEIGHTS_PORTS) {stream_fifo = 0; stream_id ++; }
				bit = 0; converter = 0;
			}
		}
		if (bit > 0 || stream_fifo > 0) {
			if (bit > 0) weights_stream[stream_fifo++][stream_id] = converter;
			while(stream_fifo < AXI_WEIGHTS_PORTS) { weights_stream[stream_fifo++][stream_id] = 0; }
			stream_id++;
		}
		bit = 0; converter = 0; stream_fifo = 0;
	}
}

#endif /* _START_H_ */
