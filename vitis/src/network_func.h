#ifndef _NETWORK_FUN_H_
#define _NETWORK_FUN_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "snn_defs.h"

// Function prototypes
bool step_izhi(float *membrane_v, float *recovery_v, float in_c);
bool step_LIF(float *membrane_v, float input_v);
void forward_izhi(float* in_c, bool*output_spk, uint32_t n_neurons, uint32_t n_steps);
void forward_LIF(float* in_c, bool*output_spk, uint32_t n_neurons, uint32_t n_steps);
void forward_linear_in(float*in_c, uint32_t n_in, float*out_c, uint32_t n_out, 
    float*weights, float*biases, uint32_t n_steps);
int forward_network(float* in_c, uint32_t n_in, bool*out_spk, uint32_t*n_layer,
    uint32_t n_layers, float*weights, float*biases, uint32_t neuron);

#endif /* _NETWORK_FUN_H_ */
