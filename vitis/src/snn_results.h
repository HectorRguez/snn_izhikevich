#ifndef _SNN_RESULTS_H_
#define _SNN_RESULTS_H_

// Common libraries
#include <stdio.h>
#include <stdlib.h>
#include "snn_defs.h"

void persist_hw_results(bool* neuron_type, uint64_t* out_stream) {

	int32_t t, x, l, xl;
	int32_t firing_rate[NUMBER_OF_NEURONS];
	{
		for (x = 0; x < NUMBER_OF_NEURONS; x++) firing_rate[x] = 0;
		uint64_t* firings = out_stream;
		printf("Persisting all neuron firing HW results...\n");
		for (t = 0; t < RUN_STEPS - 1; t++) {
			for (x = 0, l = 0; l < NUMBER_OF_LAYERS; l++) for (xl = 0; xl < NEURONS_PER_LAYER; xl++, x++) {
				int32_t f_bit = x%AXI_SIZE;
				int32_t f_idx = (x/AXI_SIZE) + AXI_POTENTIAL_OUTPUT_LENGTH;
				if ( (firings[t * AXI_OUTPUT_LENGTH + f_idx] & (uint64_t)1 << f_bit) >> f_bit)
				{
					firing_rate[x] ++;
					if (*(neuron_type + l*NEURONS_PER_LAYER + xl))
						printf("%lu,%lu\n", t, x);
					else
						printf("%lu,%lu,\n", t, x);
				}
			}
		}
		/* TODO
		printf("Persisting HW firing rates...\n");
		for (x = 0; x < NUMBER_OF_NEURONS; x++) {
			printf("%lu,%f\n", x, (((float)firing_rate[x]*1000)/(RUNTIME_MS-2*INPUT_FIRINGS_OFFSET)));
		}
		*/
	}
	{
		float *v_to_plot = (float*)out_stream;
		printf("Persisting neuron HW potentials...\n");
		for (t = 0; t < RUN_STEPS - 1; t++) {
			int v_idx = (t * AXI_OUTPUT_LENGTH * 2) + 0;
			printf("%lu,%f\n", t, v_to_plot[v_idx]);
			
		}
	}
}

#endif /* _SNN_RESULTS_H_ */