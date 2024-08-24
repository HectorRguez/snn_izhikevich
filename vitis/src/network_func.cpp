#include "network_func.h"

// Precalc Izhikevich coefficients 
// [https://www.mdpi.com/2079-9292/13/5/909]
const float a1 = 1.0;
const float a2 = -0.210;
const float a3 = -0.019;
const float b1 = -1.0/32.0;
const float b2 = -1.0/32.0;
const float b3 = 0.0;
const float c = 0.105;
const float d = 0.412;
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

bool step_LIF(float *membrane_v, float input_v){
    bool spike = *membrane_v > vth;
    *membrane_v = input_v + *membrane_v * beta; // Input + Exponential decay
    if(spike) *membrane_v -= vth;               // Reset
    return spike;
}

void forward_izhi(float* in_c, bool*output_spk, int n_neurons){
    for(int i = 0; i < n_neurons; i++){
        float membrane_v = 0, recovery_v = 0;
        for(int j = 0; j < NUM_STEPS; j++){
            output_spk[i*NUM_STEPS + j] = 
                step_izhi(&membrane_v, &recovery_v, in_c[i*NUM_STEPS+j]);
        }
    }
}

void forward_LIF(float* in_c, bool*output_spk, int n_neurons){
    for(int i = 0; i < n_neurons; i++){
        float membrane_v = 0;
        for(int j = 0; j < NUM_STEPS; j++){
            output_spk[i*NUM_STEPS + j] = 
                step_LIF(&membrane_v, in_c[i*NUM_STEPS + j]);
        }
    }
}

void forward_linear_in(float*in_c, int n_in, float*out_c, int n_out, 
    float*weights, float*biases){

    for(int i = 0; i < n_out; i++){
        // Initialize output to the bias value
        for(int k = 0; k < NUM_STEPS; k++){
            out_c[i*NUM_STEPS+k] = biases[i];
        }
        // Add weighted inputs
        for(int j = 0; j < n_in; j++){  
            for(int k = 0; k < NUM_STEPS; k++){
                out_c[i*NUM_STEPS+k] += weights[i*n_in+j]*in_c[j];
            }
        }
    }
}

void forward_linear_spk(bool*in_spk, int n_in, float*out_c, int n_out, 
    float*weights, float*biases){

    for(int i = 0; i < n_out; i++){
        // Initialize output to the bias value
        for(int k = 0; k < NUM_STEPS; k++){
            out_c[i*NUM_STEPS+k] = biases[i];
        }
        // Add weighted inputs
        for(int j = 0; j < n_in; j++){  
            float value = weights[i*n_in+j];
            for(int k = 0; k < NUM_STEPS; k++){
                out_c[i*NUM_STEPS+k] += 
                    (in_spk[j*NUM_STEPS+k]) ? value : 0;
            }
        }
    }
}

int forward_network(float* in_c, uint32_t n_in, bool*out_spk, uint32_t*n_layer,
    uint32_t n_layers, float*weights, float*biases, enum Neuron_type Neuron){

    // Neuron type
    void (*forward)(float*, bool*, int);
    switch(Neuron){
        case IZHI:
            forward = &forward_izhi;
            break;
        case LIF:
            forward = &forward_LIF;
            break;
        default:
            return(-1);
    }

    // Layer output pointers
    float out_linear_c[MAX_LAYER_SIZE*NUM_STEPS];
    bool out_neuron_spk[MAX_LAYER_SIZE*NUM_STEPS];
    
    // First layer (floating inputs)
    if(n_layers < 1) return(-1);

    // Execute linear 
    forward_linear_in(in_c, n_in, out_linear_c, n_layer[0], weights, biases);

    // Execute neuron
    (*forward)(out_linear_c, out_neuron_spk, n_layer[0]);
    
    // Advance weight and bias pointers
    weights += n_in * n_layer[0];
    biases += n_layer[0];

    // N layers
    for(uint32_t i = 1; i < n_layers; i++){
        // Execute linear
        forward_linear_spk(out_neuron_spk, n_layer[i-1], 
                out_linear_c, n_layer[i], weights, biases);

        // Execute neuron
        (*forward)(out_linear_c, out_neuron_spk, n_layer[i]);

        // Advance weight and bias pointers
        weights += n_layer[i-1]*n_layer[i];
        biases += n_layer[i];
    }

    // Write outputs
    memcpy(out_spk, out_neuron_spk, 
        NUM_STEPS*n_layer[n_layers-1]*sizeof(*out_spk));

    return 0;
}

int rate_code_result(bool*out_spk, int n_out){
    // Count the number of spikes on each output neuron
    int absolute_freq[MAX_LAYER_SIZE] = {0};
    for(int i = 0; i < n_out; i++){
        for(int j = 0; j < NUM_STEPS; j++){
            if(out_spk[i*NUM_STEPS+j]) absolute_freq[i]++;
        }
    }
    // Count the maximum number of spikes
    int max_freq = 0, max_freq_idx = 0;
    for(int i = 0; i < n_out; i++){
        if(absolute_freq[i] > max_freq){
            max_freq = absolute_freq[i];
            max_freq_idx = i;
        }
    }
    return (max_freq_idx); 
}
