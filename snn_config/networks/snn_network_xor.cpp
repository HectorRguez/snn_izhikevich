#include "snn_network_xor.h"

// Specialized methods/variables
static uint32_t trial_number;
static float t_shift_error_accum;
static float t_shift_error[NUM_TRAINING_TRIALS];
static float w_error[2*NEURONS_PER_LAYER][NUM_TRAINING_TRIALS];
static float trial_success[NUM_TRAINING_TRIALS];
static float learning_success[NUM_TRAINING_TRIALS];
static float t_spikes_trials[NUM_TRAINING_TRIALS];

// Inputs/Outputs
static float t_input_trials[NUM_INPUTS][NUM_TRAINING_TRIALS];
static float t_output_trials[NUM_TRAINING_TRIALS];

static float t_spiked[NUMBER_OF_NEURONS];
static uint32_t total_correct;
static uint32_t valid_trial;

static char p_set_inputs[NUM_INPUTS][RUN_STEPS];


// Methods
char get_neuron_type(int32_t l, int32_t xl) {
	if (l < OUTPUT_LAYER) return get_random() < INHIBITORY_NEURON_PERC;
	else return EXCITATORY_NEURON;
}

char get_spike(int32_t t, int32_t x) {
	if (x < NUM_INPUTS) return p_set_inputs[x][t];
	else return 0;
}

float exp_window(float t_pre, float t_post){
	float delta_t = t_pre - t_post;
	if (t_pre == INFINITY && t_post == INFINITY) {
		return ALPHA_PLUS;
	} else if (delta_t < 0) {
		return ALPHA_PLUS * exp(delta_t/TAU_PLUS);
	} else {
		return ALPHA_MINUS * exp((delta_t * -1.0)/TAU_MINUS);
	}
}

float get_new_weight(float current_weight, float delta_weight) {
	if (delta_weight >= 0)
		return current_weight + LEARNING_RATE(learning_success[trial_number]) * delta_weight * (W_MAX - current_weight);
	else
		return current_weight + LEARNING_RATE(learning_success[trial_number]) * delta_weight * (current_weight - W_MIN);
}

float get_weight(float* synapse_weights, int32_t l, int32_t xl, int32_t x, int32_t y, char feedback) {
	if (feedback == 0) { // Initial phase
		if (l == 0 && y < NUM_INPUTS) { // Input-Hidden layer
			return 0.06 + (get_random() / 50);
		} else if (l > 0 && l < OUTPUT_LAYER) { // Hidden-Output layer
			return (get_random() / 10); //- 0.05;
		} else if (l == OUTPUT_LAYER && xl < NUM_OUTPUTS) { // Hidden-Output layer
			return 0.10 + (get_random() / 10); //- 0.05;
		}
	} else { // Feedback phase
		//float delta = weights_delta[x][y];
		//if (delta > 3) delta = 3;
		//if (delta < -3) delta = -3;

		// IMPORTANT: Correct this line
		return *(synapse_weights + x * NEURONS_PER_LAYER + y);// - (LEARNING_RATE * delta);
	}
	return 0;
}

void refresh_delta_weights(float* synapse_weights) {
	int32_t x, l, xl, y;
	for (l = HIDDEN_LAYERS; l >=0; l--) {
		for (xl = 0; xl < NEURONS_PER_LAYER; xl++) {
			// Calculate position of the neuron that is undergoing weight changes 
			x = (l * NEURONS_PER_LAYER) + xl;

			// IMPORTANT: I do not understand the purpose of this line
			if (l == OUTPUT_LAYER && xl >= NUM_OUTPUTS) break;

			// Index of the first neuron that is on the next layer
			int32_t post_layer_idx = ((l + 1) * NEURONS_PER_LAYER);

			// Index of the first neuron that is on the previous layer
			int32_t previous_layer_idx = ((l - 1) * NEURONS_PER_LAYER);

			// Iterate all pre-synaptic connections
			for (y = 0; y < NEURONS_PER_LAYER; y++) {
				float* synapse_weight = synapse_weights + x * NUMBER_OF_NEURONS + y;
				// Process only non-null synapses
				if (l == OUTPUT_LAYER && xl < NUM_OUTPUTS) { // Output-Hidden

					float t1 = exp_window(t_spiked[previous_layer_idx + y], t_output_trials[trial_number]);
					float t2 = exp_window(t_spiked[previous_layer_idx + y], t_spiked[x]);
					*synapse_weight = get_new_weight(*synapse_weight, t1 - t2);

					w_error[y][trial_number] = *synapse_weight;

				} else if (l == 0 && y < NUM_INPUTS) { // Hidden-Input

					float t1 = exp_window(t_input_trials[y][trial_number], t_output_trials[trial_number]);
					float t2 = exp_window(t_input_trials[y][trial_number], t_spiked[OUTPUT_NEURON]);
					*synapse_weight = get_new_weight(*synapse_weight, t1 - t2);

					w_error[x+NEURONS_PER_LAYER][trial_number] = *synapse_weight;
				}
			}
		}
	}
}

void generate_inputs() {
	uint32_t pattern = 0;
	uint32_t t = 0;
	for (int32_t trial = 0; trial < NUM_TRAINING_TRIALS; trial++) {

		// Get random inputs
		float operand_1 = get_random() < 0.5; 
		float operand_2 = get_random() < 0.5; 

		// Set the timing inputs
		t_input_trials[0][trial] = DELAY_REFERENCE;
		t_input_trials[1][trial] = operand_1 == 0? DELAY_INPUT_LOW_MS : DELAY_INPUT_HIGH_MS;
		t_input_trials[2][trial] = operand_2 == 0? DELAY_INPUT_LOW_MS : DELAY_INPUT_HIGH_MS;

		// Set target output
		t_output_trials[trial] =  (operand_1 == operand_2? DELAY_OUTPUT_LOW_MS: DELAY_OUTPUT_HIGH_MS);
		
		// Store potential inputs
		for (int32_t trial_ms = 0; trial_ms < TRIAL_TIME_MS; trial_ms++, t++)
			for (int32_t input = 0; input < NUM_INPUTS; input++) p_set_inputs[input][t] = (t_input_trials[input][trial] == trial_ms);
	}
}

void feedback_error(uint64_t* out_hw, float* synapse_weights, int32_t t) {
	int32_t t_start = t + 1 - TRIAL_TIME_MS;
	
	// Put all the spiking times to infinity by default
	for(int8_t i = 0; i < NUMBER_OF_NEURONS; i++)
	{
		t_spiked[i] = INFINITY;
	} 

	// Read the spiking times of each neuron
	for(int32_t i = 0; i < TRIAL_TIME_MS; i++)
	{
		uint64_t spikes = *(out_hw + AXI_POTENTIAL_OUTPUT_LENGTH + t_start + i * AXI_OUTPUT_LENGTH); // 6th and 3rd neuron
		for (int n = 0; n < NUMBER_OF_NEURONS; n++)
		{
			uint64_t buffer = spikes;
			uint64_t mask = 0b1;
			uint8_t pos = (sizeof(uint64_t) * 8) - n - 1;
			buffer = buffer >> pos;
			if(buffer & mask)
			{
				t_spiked[n] = i;
			}
		}
	}

	// Initialize global errors
	t_shift_error[trial_number] = 0;
	int32_t error = (int32_t)(t_spiked[OUTPUT_NEURON] - t_output_trials[trial_number]);

	// Update the number of correct trials
	// Update the trial_success array at the trial_number
	if (abs(error) <= THRESHOLD_FREQ) {
		total_correct ++; trial_success[trial_number] = 1;
	} else {
		trial_success[trial_number] = 0;
	}

	// Update the spiking type of the spike time array at the trial number
	t_spikes_trials[trial_number] = t_spiked[OUTPUT_NEURON];

	/* Compute the learning success by calculating the learning success of the previous
	   1000 trials */
	int32_t total_trials = 0;
	int32_t correct_trials = 0;
	for (uint32_t k = 0; k < 1000; k++) {
		if (trial_number > k) {
			total_trials ++;
			if (trial_success[trial_number - k] > 0) correct_trials ++;
		}
	}
	learning_success[trial_number] = (float)correct_trials/(float)(total_trials+1);

	/* Limit the maximum error as the trial time divided by 2.
	   If the error is below the trial time divided by 2, 
	   square it and divide it by 2 (remove sign)


	   IMPORTANT: CONCERNS REGARDING THE SQUARE COMPONENT.
	   Error that are almost at the TRIAL_TIME_MS / 2 limit are way bigger than errors that 
	   Surpass that value. 
	   
	   E.g., error = +-24 --> +22
	   	     error = +-21 --> 21 * 21 / 2 =  220.5		*/

	
	if (error > TRIAL_TIME_MS/2 || error < -TRIAL_TIME_MS/2)
		t_shift_error[trial_number] = TRIAL_TIME_MS/2;
	else
		t_shift_error[trial_number] = (error*error)/2;


	// Refresh delta weights
	refresh_delta_weights(synapse_weights);

	trial_number ++;
}
void persist_trials()
{
	printf("Global learning accuracy: %.3f\n", learning_success[NUM_TRAINING_TRIALS-2]);
}

void persist_app_results(bool* neuron_type, uint64_t* out_hw) {
	persist_trials();
}