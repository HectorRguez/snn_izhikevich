#ifndef _SNN_NETWORK_DEFS_H
#define _SNN_NETWORK_DEFS_H


/*****************************************************************************
 *                          General Configuration        	                 *
 *****************************************************************************/
/* Precision types */
#define FIXED_POINT			0  // FPGA_CLK =  8ns (HLS CLK: 7ns, Estimated: 6.38ns)
#define FLOATING_POINT		1  // FPGA_CLK = 10ns (HLS CLK: 9ns, Estimated: 8.42ns)

/* App type */
#define APP_RANDOM			0
#define APP_XOR				1
#define APP_ADDER			2
#define APP_PATTERN			3
#define APP_SINGLE			4


/*****************************************************************************
 *                               APP_XOR	        	                     *
 *****************************************************************************/
#if APP_TYPE == APP_XOR


#elif APP_TYPE == APP_SINGLE
/*****************************************************************************
 *                               APP_SINGLE	        	                     *
 *****************************************************************************/
#define NUM_TRAINING_TRIALS		1000

// Network structure
#define HIDDEN_LAYERS			1
#define SIZE_LAYERS				(HIDDEN_LAYERS + 1)
#define OUTPUT_LAYER 			HIDDEN_LAYERS
#define SIZE_NEURONS_PER_LAYER	4
#define OUTPUT_NEURON			SIZE_NEURONS_PER_LAYER
#define NUM_INPUTS				1
#define NUM_OUTPUTS				1

// Learning defines
#define ALPHA_PLUS				0.02f
#define ALPHA_MINUS				-0.02f
#define TAU_PLUS				18
#define TAU_MINUS				18
#define W_MAX					5
#define W_MIN					-5
#define INHIBITORY_NEURON_PERC	0.2f
#define LEARNING_RATE			0.2//0.05

// Delays
#define TRIAL_TIME_MS			100

#define INPUT_SPIKES			3
#define OUTPUT_SPIKES			3
#define INPUT_MS				(TRIAL_TIME_MS/INPUT_SPIKES)
#define OUTPUT_MS				(TRIAL_TIME_MS/OUTPUT_SPIKES)
#define INPUT_FREQ				(1000/INPUT_MS)
#define OUTPUT_FREQ				(1000/OUTPUT_MS)

#define THRESHOLD_FREQ			5//((OUTPUT_HIGH_FREQ - OUTPUT_LOW_FREQ) / 2)
#define MIDDLE_FREQ				((OUTPUT_HIGH_FREQ + OUTPUT_LOW_FREQ) / 2)

// Misc
#define RUNTIME_MS 				(NUM_TRAINING_TRIALS * TRIAL_TIME_MS)

#define PERSIST_APP_RESULTS
#define NEURON_TO_PLOT			OUTPUT_NEURON

#elif APP_TYPE == APP_ADDER
/*****************************************************************************
 *                               APP_ADDER	        	                     *
 ******************************************************************************/
#define ADDER_BITS				1

#if ADDER_BITS <= 3
#define NUM_TRAINING_TRIALS		20000
#define DELAY_OUTPUT_MS			10 //9
#elif ADDER_BITS <= 5
#define NUM_TRAINING_TRIALS		800
#define DELAY_OUTPUT_MS			8
#elif ADDER_BITS <= 7
#define NUM_TRAINING_TRIALS		1500
#define DELAY_OUTPUT_MS			8
#endif

// Network structure
#define HIDDEN_LAYERS			1
#define SIZE_LAYERS				(HIDDEN_LAYERS + 1)
#define SIZE_NEURONS_PER_LAYER	2
// Input/Outputs
#define NUM_INPUTS				(ADDER_BITS + ADDER_BITS + 1)
#define NUM_OUTPUTS				(ADDER_BITS /*+ 1*/)
// Learning defines
#define ALPHA_POST				0.80f
#define ALPHA_PRE				-0.30f
#define INHIBITORY_NEURON_PERC	0.05f
#define LEARNING_RATE			0.001f //0.05
// Delays
#define TRIAL_TIME_MS			100
#define DELAY_REFERENCE			0
#define DELAY_INPUT_LOW_MS		0
#define DELAY_INPUT_HIGH_MS		6 //4
#define DELAY_OUTPUT_LOW_MS		10
#define DELAY_OUTPUT_HIGH_MS	(10 + 6)
#define PASSING_THRESHOLD		2 // <=round_down(OUTPUT_HIGH - OUTPUT_LOW)/2
// Misc
#define TAU_PARAM				TAU_S
#define RUNTIME_MS 				(NUM_TRAINING_TRIALS * TRIAL_TIME_MS)
#define OUTPUT_NEURONS			(SIZE_NEURONS_PER_LAYER * HIDDEN_LAYERS)
#define OUTPUT_LAYER 			HIDDEN_LAYERS

#define PERSIST_APP_RESULTS
#define NEURON_TO_PLOT			OUTPUT_NEURONS

#elif APP_TYPE == APP_PATTERN
/*****************************************************************************
 *                              APP_PATTERN	        	                     *
 ******************************************************************************/
#define NUM_TRAINING_TRIALS		2000
#define DELAY_OUTPUT_MS			10 //9

// Network structure
#define SIZE_LAYERS				2
#define OUTPUT_LAYER 			1
#define HIDDEN_LAYER			0
#define SIZE_NEURONS_PER_LAYER	10
#define OUTPUT_NEURON			SIZE_NEURONS_PER_LAYER
#define MAX_TRIAL_SPIKES		10

// Learning defines
#define ALPHA_POST				0.80f
#define ALPHA_PRE				-0.30f
#define INHIBITORY_NEURON_PERC	0.05f
#define LEARNING_RATE			0.001f //0.05

// Delays
#define TRIAL_TIME_MS			100
#define DELAY_REFERENCE			0
#define DELAY_INPUT_LOW_MS		0
#define DELAY_INPUT_HIGH_MS		6 //4
#define DELAY_OUTPUT_LOW_MS		10
#define DELAY_OUTPUT_HIGH_MS	(10 + 6)
#define PASSING_THRESHOLD		2 // <=round_down(OUTPUT_HIGH - OUTPUT_LOW)/2
// Misc
#define TAU_PARAM				TAU_S
#define RUNTIME_MS 				(NUM_TRAINING_TRIALS * TRIAL_TIME_MS)

#define PERSIST_APP_RESULTS
#define NEURON_TO_PLOT			OUTPUT_NEURON

#endif /* APP_TYPE */

#define RUN_STEPS 				(int32_t)(RUNTIME_MS / SIM_TIMESTEP_MS)

#endif /* _SNN_NETWORK_DEFS_H */
