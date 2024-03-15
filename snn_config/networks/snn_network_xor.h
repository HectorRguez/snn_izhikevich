#ifndef _SNN_NETWORK_XOR_H
#define _SNN_NETWORK_XOR_H

// Common libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/*****************************************************************************
 *                              Utils Definitions   	                     *
 *****************************************************************************/

#define PRAGMA_SUB(x) 				_Pragma (#x)
#define PRAGMA_HLS(x)				PRAGMA_SUB(x)

#define get_random() 				((float)rand() / (float)RAND_MAX) // random float between 0 and 1
#define round_div_upper(x, y) 		((int32_t)((x + y - 1 ) / y))
#define bits_size(type) 			(sizeof(type) * 8)

#define NUM_TRAINING_TRIALS		2000

// Network structure
#define HIDDEN_LAYERS			1 // 1
#define SIZE_LAYERS				(HIDDEN_LAYERS + 1)
#define OUTPUT_LAYER 			HIDDEN_LAYERS
#define SIZE_NEURONS_PER_LAYER	6
#define OUTPUT_NEURON			(OUTPUT_LAYER*SIZE_NEURONS_PER_LAYER)
#define NUM_INPUTS				3
#define NUM_OUTPUTS				1

// Model time step
#define TIMESTEP_MS 					0.5f
#define SIM_TIMESTEP_MS					(2 * TIMESTEP_MS)
#define RUN_STEPS 						(int32_t)(RUNTIME_MS / SIM_TIMESTEP_MS)

//Neural network dimensions
#define NUMBER_OF_LAYERS 				SIZE_LAYERS
#define NEURONS_PER_LAYER 				SIZE_NEURONS_PER_LAYER
#define NUMBER_OF_NEURONS 				(NUMBER_OF_LAYERS * NEURONS_PER_LAYER)
#define NUMBER_OF_SYNAPSES				(NUMBER_OF_NEURONS * NEURONS_PER_LAYER)

// Probability that the neuron is a inhibitory neuron
#define PROBABILITY_INHIBITORY_NEURON 	0.1f //0.1

//Neuron types excitatory and inhibitory
#define EXCITATORY_NEURON 				0
#define INHIBITORY_NEURON 				1

// Learning defines
#define ALPHA_PLUS				0.020f
#define ALPHA_MINUS				-0.015f
#define TAU_PLUS				14 // 12
#define TAU_MINUS				14 // 12
#define W_MAX					10
#define W_MIN					-10
#define INHIBITORY_NEURON_PERC	0.20f // 0.20
#define LEARNING_RATE(progress)	(progress < 0.40f ? 0.14f: (\
								 progress < 0.60f ? 0.11f : (\
								 progress < 0.70f ? 0.08f : (\
								 progress < 0.80f ? 0.05f : (\
								 progress < 0.90f ? 0.02f : (\
								 progress < 0.99f ? 0.001f : 0.000f)))))) // 0.12 // 40-50, 60-100, 80-500, 90-1000

// Delays
#define TRIAL_TIME_MS			45 // 100
#define DELAY_REFERENCE			0
#define DELAY_INPUT_LOW_MS		0
#define DELAY_INPUT_HIGH_MS		6 // 5
#define DELAY_OUTPUT_LOW_MS		11 // 7
#define DELAY_OUTPUT_HIGH_MS	(11 + 6) // 7 + 6
#define THRESHOLD_FREQ			((DELAY_OUTPUT_HIGH_MS - DELAY_OUTPUT_LOW_MS) / 2)

// Misc
#define RUNTIME_MS 				(NUM_TRAINING_TRIALS * TRIAL_TIME_MS)

#define PERSIST_APP_RESULTS
#define NEURON_TO_PLOT			OUTPUT_NEURON

// Firing voltage
#define FIRING_VOLTAGE                  35.0f

/*****************************************************************************/
/*            		         Input/Output Definitions                        */
/*****************************************************************************/
// AXI ports size
#define AXI_SIZE					64
#define AXIL_SIZE					32

// Network (Input)
#define AXI_NEURON_TYPE_LENGTH		round_div_upper(NUMBER_OF_NEURONS, AXI_SIZE)

// Synapses (Input)
#define AXI_INPUT_LENGTH			round_div_upper(INPUT_SYNAPSES, AXIL_SIZE)

// Weights (Input)
#if PRECISION_TYPE == FIXED_POINT
#define POTENTIAL_BITS				32
#define POTENTIAL_BITS_INT 			10
#define POTENTIAL_BITS_FRACTIONAL	(POTENTIAL_BITS - POTENTIAL_BITS_INT - 1)
#define SYNAPSE_BITS				32 //16
#define	SYNAPSE_BITS_INT			5
#define SYNAPSE_BITS_FRACTIONAL		(SYNAPSE_BITS - SYNAPSE_BITS_INT)
#define WEIGHT_BITS					16 //8
#define WEIGHT_SCALE_BITS 			3
#define WEIGHT_SCALE 				8.0f // Equal to 2^WEIGHT_SCALE_BITS
#elif PRECISION_TYPE == FLOATING_POINT
#define WEIGHT_BITS					32
#define WEIGHT_SCALE 				1.0f // No scaling
#endif
#define AXI_WEIGHTS_PORTS			4
#define AXI_WEIGHTS_THROUGHPUT		(AXI_SIZE * AXI_WEIGHTS_PORTS)
#define AXI_WEIGHTS_LINE_LENGHT		round_div_upper(WEIGHT_BITS * NEURONS_PER_LAYER, AXI_WEIGHTS_THROUGHPUT)
#define AXI_WEIGHTS_LINE_BITS		(AXI_WEIGHTS_LINE_LENGHT * AXI_WEIGHTS_THROUGHPUT)
#define AXI_WEIGHTS_LENGTH			(AXI_WEIGHTS_LINE_LENGHT * NUMBER_OF_NEURONS)

// Output
#define AXI_POTENTIAL_OUTPUTS		2
#define AXI_POTENTIAL_OUTPUT_LENGTH	round_div_upper(AXI_POTENTIAL_OUTPUTS * bits_size(float), AXI_SIZE)
#define AXI_FIRINGS_LENGTH			round_div_upper(NUMBER_OF_NEURONS, AXI_SIZE)
#define AXI_OUTPUT_LENGTH			(AXI_POTENTIAL_OUTPUT_LENGTH + AXI_FIRINGS_LENGTH)



// Common interface
char get_neuron_type(int32_t l, int32_t xl);
char get_spike(int32_t t, int32_t x);
float get_weight(float* synapse_weights, int32_t l, int32_t xl, int32_t x, int32_t y, char feedback);
void generate_inputs();
void persist_app_results(bool* neuron_type, uint64_t* out_hw);
void feedback_error(uint64_t* out_hw, float* synapse_weights, int32_t t);

#endif /* _SNN_NETWORK_XOR_H */