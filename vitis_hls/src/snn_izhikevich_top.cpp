#include "snn_types.h"
#include "../../snn_config/snn_defs.h"

// Precalc Izhikevich coefficients 
// [https://www.mdpi.com/2079-9292/13/5/909]
const fixed_t a1  = 1.0;
const fixed_t a2  = -0.210;
const fixed_t a3  = -0.019;
const fixed_t b1  = -1.0/32.0;
const fixed_t b2  = -1.0/32.0;
const fixed_t b3  = 0.0;
const fixed_t c   = 0.105;
const fixed_t d   = 0.412;
const fixed_t vth = 0.7;


void forward_linear_in(fixed_t*in_c, uint6_t n_in, fixed_t*out_c, uint6_t n_out,
    hls_stream_64_t& input_stream0,hls_stream_64_t& input_stream1,hls_stream_64_t& input_stream2,hls_stream_64_t& input_stream3){
	
	// Load input biases
	fixed_t biases[MAX_LAYER_SIZE];
	linear_load_biases: for(uint6_t i = 0; i < MAX_LAYER_SIZE; i+=8){
		// Input stream 0
			uint64_t input0 = input_stream0.read().data;
			uint32_t input0_h = input0.range(63, 32);
			uint32_t input0_l = input0.range(31, 0);
			biases[j+1] = *(fixed_t*)&input0_h;
			biases[j] = *(fixed_t*)&input0_l;

			// Input stream 1
			uint64_t input1 = input_stream1.read().data;
			uint32_t input1_h = input1.range(63, 32);
			uint32_t input1_l = input1.range(31, 0);
			biases[j+3] = *(fixed_t*)&input1_h;
			biases[j+2] = *(fixed_t*)&input1_l;

			// Input stream 2
			uint64_t input2 = input_stream2.read().data;
			uint32_t input2_h = input2.range(63, 32);
			uint32_t input2_l = input2.range(31, 0);
			biases[j+5] = *(fixed_t*)&input2_h;
			biases[j+4] = *(fixed_t*)&input2_l;

			// Input stream 3
			uint64_t input3 = input_stream3.read().data;
			uint32_t input3_h = input3.range(63, 32);
			uint32_t input3_l = input3.range(31, 0);
			biases[j+7] = *(fixed_t*)&input3_h;
			biases[j+6] = *(fixed_t*)&input3_l;
	}
	

    linear_outer_loop: for(uint6_t i = 0; i < MAX_LAYER_SIZE; i++){
		#pragma HLS PIPELINE II=45

		// Load weights buffer
		fixed_t weight_buffer[MAX_LAYER_SIZE];
		#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=weight_buffer
		linear_load_weight: for(uint6_t j = 0; j < MAX_LAYER_SIZE; j+=8){
			// Input stream 0
			uint64_t input0 = input_stream0.read().data;
			uint32_t input0_h = input0.range(63, 32);
			uint32_t input0_l = input0.range(31, 0);
			weight_buffer[j+1] = *(fixed_t*)&input0_h;
			weight_buffer[j] = *(fixed_t*)&input0_l;

			// Input stream 1
			uint64_t input1 = input_stream1.read().data;
			uint32_t input1_h = input1.range(63, 32);
			uint32_t input1_l = input1.range(31, 0);
			weight_buffer[j+3] = *(fixed_t*)&input1_h;
			weight_buffer[j+2] = *(fixed_t*)&input1_l;

			// Input stream 2
			uint64_t input2 = input_stream2.read().data;
			uint32_t input2_h = input2.range(63, 32);
			uint32_t input2_l = input2.range(31, 0);
			weight_buffer[j+5] = *(fixed_t*)&input2_h;
			weight_buffer[j+4] = *(fixed_t*)&input2_l;

			// Input stream 3
			uint64_t input3 = input_stream3.read().data;
			uint32_t input3_h = input3.range(63, 32);
			uint32_t input3_l = input3.range(31, 0);
			weight_buffer[j+7] = *(fixed_t*)&input3_h;
			weight_buffer[j+6] = *(fixed_t*)&input3_l;
		}

    	if(i < n_out){
    		// Initialize output to the bias value
			linear_init_variables: for(uint6_t j = 0; j < NUM_STEPS; j++){
				out_c[i*NUM_STEPS+j] = biases[i];
			}
			// Multiply inputs and accumulate
			linear_compute_timesteps: for(uint6_t j = 0; j < NUM_STEPS; j++){
				linear_multiply_loop: for(uint6_t k = 0; k < MAX_LAYER_SIZE; k+=16){
					out_c[i*NUM_STEPS+j] += weight_buffer[k+15]*in_c[(k+15)*NUM_STEPS+j] +
										weight_buffer[k+14]*in_c[(k+14)*NUM_STEPS+j] +
										weight_buffer[k+13]*in_c[(k+13)*NUM_STEPS+j] +
										weight_buffer[k+12]*in_c[(k+12)*NUM_STEPS+j] +
										weight_buffer[k+11]*in_c[(k+11)*NUM_STEPS+j] +
										weight_buffer[k+10]*in_c[(k+10)*NUM_STEPS+j] +
										weight_buffer[k+9]*in_c[(k+9)*NUM_STEPS+j] +
										weight_buffer[k+8]*in_c[(k+8)*NUM_STEPS+j] +
										weight_buffer[k+7]*in_c[(k+7)*NUM_STEPS+j] +
										weight_buffer[k+6]*in_c[(k+6)*NUM_STEPS+j] +
										weight_buffer[k+5]*in_c[(k+5)*NUM_STEPS+j] +
										weight_buffer[k+4]*in_c[(k+4)*NUM_STEPS+j] +
										weight_buffer[k+3]*in_c[(k+3)*NUM_STEPS+j] +
									    weight_buffer[k+2]*in_c[(k+2)*NUM_STEPS+j] +
										weight_buffer[k+1]*in_c[(k+1)*NUM_STEPS+j] +
										weight_buffer[k]*in_c[k*NUM_STEPS+j];
				}
			}
    	}
    }
}

uint1_t hls_snn_izikevich(
		uint1_t state,
		uint32_t in_c[MAX_LAYER_SIZE],
		uint32_t n_in,
		uint32_t n_out,
		uint32_t n_layers,
		uint32_t n_layer[MAX_LAYER_COUNT],
		hls_stream_64_t& input_stream0,
		hls_stream_64_t& input_stream1,
		hls_stream_64_t& input_stream2,
		hls_stream_64_t& input_stream3,
		hls_stream_64_t& output_stream) {
	#pragma HLS TOP name=hls_snn_izhikevich

	#pragma HLS INTERFACE s_axilite port=return bundle=control
	#pragma HLS INTERFACE s_axilite port=state bundle=control
	#pragma HLS INTERFACE s_axilite port=in_c bundle=control
	#pragma HLS INTERFACE s_axilite port=n_in bundle=control
	#pragma HLS INTERFACE s_axilite port=n_out bundle=control
	#pragma HLS INTERFACE s_axilite port=n_layers bundle=control
	#pragma HLS INTERFACE s_axilite port=n_layer bundle=control
	#pragma HLS INTERFACE axis port=input_stream0
	#pragma HLS INTERFACE axis port=input_stream1
	#pragma HLS INTERFACE axis port=input_stream2
	#pragma HLS INTERFACE axis port=input_stream3
	#pragma HLS INTERFACE axis port=output_stream

	// Layer input-output pointers
    fixed_t out_linear_c[MAX_LAYER_SIZE*NUM_STEPS];
	#pragma HLS ARRAY_PARTITION dim=1 factor=16 type=block variable=out_linear_c
    fixed_t out_neuron_spk[MAX_LAYER_SIZE*NUM_STEPS];
	#pragma HLS ARRAY_PARTITION dim=1 factor=16 type=block variable=out_neuron_spk

	// Process logic
	if (state == STATE_INIT) {
		// Read inputs
		read_inputs: for(uint6_t i = 0; i < MAX_LAYER_SIZE; i++){
			for(uint6_t j = 0; j < NUM_STEPS; j++){
				if(i < n_in){
					out_neuron_spk[i*NUM_STEPS+j] = *(fixed_t*)(in_c + i);
				}
				else{
					out_neuron_spk[i*NUM_STEPS+j] = 0;
				}
			}
		}
	}
	else { // state == STATE_PROCESS

		// Execute network
		uint6_t n_prev_layer = n_in;
		layer_propagation: for(uint6_t i = 0; i < MAX_LAYER_COUNT; i++){
			if(i < n_layers){
				// Execute linear
				forward_linear_in(out_neuron_spk, n_prev_layer,
						out_linear_c, n_layer[i], input_stream0, input_stream1, input_stream2, input_stream3);
			// Execute neuron
				izhi_outer_loop: for(uint6_t j = 0; j < MAX_LAYER_SIZE; j++){
				#pragma HLS UNROLL
					fixed_t membrane_v = 0, recovery_v = 0;
					izhi_compute_timesteps: for(uint6_t k = 0; k < NUM_STEPS; k++){
					#pragma HLS UNROLL off=true
					#pragma HLS PIPELINE II=16
						// Temporary variables
						fixed_t v = membrane_v, u = recovery_v, I = out_linear_c[NUM_STEPS*j+k];
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
						membrane_v = v;
						recovery_v = u;
						out_neuron_spk[NUM_STEPS*j+k] = (spike) ? 1.0 : 0.0;
					}
				}
				n_prev_layer = n_layer[i]; // Next iteration
			}
		}
		//// Write outputs
		//uint64_t data = input_stream0.read().data;
		//axis64_t stream;

		//// Send back state
		//stream.data = state;
		//stream.last = 0;
		//output_stream.write(stream);

		// Send back in_c
		//for(uint32_t i = 0; i < n_in; i++){
		//	stream.data = in_c[i];
		//	stream.last = 0;
		//	output_stream.write(stream);
		//}

		// Send back n_layer
		//for(uint32_t i = 0; i < n_layers; i++){
		//	stream.data = n_layer[i];
		//	stream.last = 0;
		//	output_stream.write(stream);
		//}

		// Send back second bias
		//uint64_t input0 = input_stream0.read().data;
		//stream.data = input0.range(63, 32);
		//stream.last = 0;
		//output_stream.write(stream);

		// Send back second weight
		//input0 = input_stream0.read().data;
		//uint32_t input0_value = input0.range(63, 32);
		//fixed_t weight_buffer1 = *(fixed_t*)&input0_value;
		//stream.data = *(uint32_t*)&weight_buffer1;
		//stream.last = 0;
		//output_stream.write(stream);

		// Send back the data that was received in input_0
		//stream.data = data;
		//stream.last = 1;
		//output_stream.write(stream);

		// Send output data
		//uint9_t data_out_idx;
		//uint64_t data_out;
		//for(int i = 0; i < MAX_LAYER_SIZE*NUM_STEPS; i++){
		//	// Get value and write it on the output buffer
		//	bool out = (out_neuron_spk[i] != 0);
		//	data_out = data_out | (out << data_out_idx++);
		//	// Check if the output is complete and send it
		//	if(data_out_idx > 63){
		//		stream_out.data = data_out;
		//		stream_out.last = 0;
		//		output_stream.write(stream_out);
		//		data_out = 0;
		//		data_out_idx = 0;
		//	}
		//}
		//stream_out.data = data_out;
		//stream_out.last = 1;
		//output_stream.write(stream_out);

		// Send simple output data
		axis64_t stream_out;
		for(int i = 0; i < MAX_LAYER_SIZE*NUM_STEPS; i++){

			// Float conversion to bool
			fixed_t out_neuron_spk_f = out_neuron_spk[i];
			uint32_t data = *(fixed_t*)&out_neuron_spk_f;
			stream_out.data = data;
			
			// LAST flag
			if(i == MAX_LAYER_SIZE*NUM_STEPS-1){
				stream_out.last = 1;
			}
			else{
				stream_out.last = 0;
			}
			output_stream.write(stream_out);
		}
	}
	return SUCCESS_OK;
}



