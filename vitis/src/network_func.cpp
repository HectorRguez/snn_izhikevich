#include "network_func.h"

// Memory size defines
#define MAX_LAYER_SIZE 30
#define NUM_STEPS 30

// Precalc Izhikevich coefficients 
// [https://www.mdpi.com/2079-9292/13/5/909]
const float a1  = 1.0;
const float a2  = -0.210;
const float a3  = -0.019;
const float b1  = -1.0/32.0;
const float b2  = -1.0/32.0;
const float b3  = 0.0;
const float c   = 0.105;
const float d   = 0.412;
const float vth = 0.7;

// LIF coefficients
const float beta = 0.95;

bool step_izhi(float *membrane_v, float *recovery_v, float in_c){
    // Temporary variables
    float v = *membrane_v, u = *recovery_v, I = in_c;
    bool spike;
    // Computation
    spike = (v >= vth);
    if(spike){
        v = c;
        u += d;
    }
    else{
        v += a1*v*v + a2*v + a3*u + I;
        u += b1*v + b2*u + b3;
    }
    // Outputs
    *membrane_v = v;
    *recovery_v = u;
    return spike;
}

void forward_izhi(float* in_c, bool*output_spk, int n_neurons, int n_steps){
    for(int i = 0; i < n_neurons; i++){
        float membrane_v = 0, recovery_v = 0;
        for(int j = 0; j < n_steps; j++){
            output_spk[i*n_steps + j] = 
                step_izhi(&membrane_v, &recovery_v, in_c[i*n_steps+j]);
        }
    }
}

void forward_linear_in(float*in_c, int n_in, float*out_c, int n_out, 
    float*weights, float*biases, int n_steps){

    for(int i = 0; i < n_out; i++){
        // Initialize output to the bias value
        for(int k = 0; k < n_steps; k++){
            out_c[i*n_steps+k] = biases[i];
        }
        // Add weighted inputs
        for(int j = 0; j < n_in; j++){  
            for(int k = 0; k < n_steps; k++){
                out_c[i*n_steps+k] += weights[i*n_in+j]*in_c[j];
            }
        }
    }
}

void forward_linear_spk(bool*in_spk, int n_in, float*out_c, int n_out, 
    float*weights, float*biases, int n_steps){

    for(int i = 0; i < n_out; i++){
        // Initialize output to the bias value
        for(int k = 0; k < n_steps; k++){
            out_c[i*n_steps+k] = biases[i];
        }
        // Add weighted inputs
        for(int j = 0; j < n_in; j++){  
            float value = weights[i*n_in+j];
            for(int k = 0; k < n_steps; k++){
                out_c[i*n_steps+k] += 
                    (in_spk[j*n_steps+k]) ? value : 0;
            }
        }
    }
}

void forward_network_izhi(float* in_c, int n_in, int n_out, bool*out_spk, int*n_layer, 
    int n_layers, float*weights, float*biases){

    // Layer output pointers
    float out_linear_c[MAX_LAYER_SIZE*NUM_STEPS];
    bool out_neuron_spk[MAX_LAYER_SIZE*NUM_STEPS];

    // Execute linear 
    forward_linear_in(in_c, n_in, out_linear_c, n_layer[0], weights, biases, NUM_STEPS);

    // Execute neuron
    forward_izhi(out_linear_c, out_neuron_spk, n_layer[0], NUM_STEPS);

    // Advance weight and bias pointers
    weights += n_in * n_layer[0];
    biases += n_layer[0];

    // N layers
    for(int i = 1; i < n_layers; i++){
        // Execute linear
        forward_linear_spk(out_neuron_spk, n_layer[i-1], 
                out_linear_c, n_layer[i], weights, biases, NUM_STEPS);

        // Execute neuron
        forward_izhi(out_linear_c, out_neuron_spk, n_layer[i], NUM_STEPS);

        // Advance weight and bias pointers
        weights += n_layer[i-1]*n_layer[i];
        biases += n_layer[i];
    }
    // Write outputs
    for(int i = 0; i < NUM_STEPS*n_out; i++){
        out_spk[i] = out_neuron_spk[i];
    }
}
