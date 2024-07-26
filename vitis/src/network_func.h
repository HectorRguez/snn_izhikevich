#ifndef _NETWORK_FUN_H_
#define _NETWORK_FUN_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Neuron type
enum Neuron_type {NONE, LIF, IZHI};

// Function prototypes
bool step_izhi(float *membrane_v, float *recovery_v, float in_c);
bool step_LIF(float *membrane_v, float input_v);
void forward_izhi(float* in_c, bool*output_spk, int n_neurons, int n_steps);
void forward_LIF(float* in_c, bool*output_spk, int n_neurons, int n_steps);
void forward_linear_in(float*in_c, int n_in, float*out_c, int n_out, 
    float*weights, float*biases, int n_steps);
void forward_linear_spk(bool*in_spk, int n_in, float*out_c, int n_out, 
    float*weights, float*biases, int n_steps);
void forward_network_izhi(float* in_c, int n_in, int n_out, bool*out_spk, int*n_layer, 
    int n_layers, float*weights, float*biases);

#endif /* _NETWORK_FUN_H_ */