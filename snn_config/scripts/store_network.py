# Imports
import sys
import torch
from array import array
import struct
import binascii

VALUES_PER_ROW = 4

# Read module state dictionary and count the number of layers
state_dict = torch.load(str(sys.argv[1]))
keysList = list(state_dict.keys())

#print('State dictionary:')
#print(state_dict)

# Network defining variables
n_inputs = 0
n_per_layer = []
weights = []
biases = []

#print('Registered network modules:')
for i in range(0, len(state_dict), 2):
    # Retrieve weights and biases
    weight_idx = keysList[i]
    bias_idx = keysList[i+1]
    #print(weight_idx)
    #print(bias_idx)

    weight = state_dict[weight_idx]
    bias = state_dict[bias_idx]

    # Read the number of inputs
    if (i == 0):
        n_inputs = weight.size(dim=1)
    
    # Read the size of the layer
    n_per_layer.append(bias.size(dim=0))

    # Flatten weights and biases
    weight = weight.flatten()
    bias = bias.flatten()

    # Transform them to list and append
    weight_list = weight.tolist()
    bias_list = bias.tolist()
    weights.extend(weight_list)
    biases.extend(bias_list)

n_outputs = n_per_layer[-1]

# File format: N_LAYERS(int) + N_INPUTS(int) + N_PER_LAYER(int) + BIASES(float) + WEIGHTS(float)

# Conversion to ascii binary array
#int_values = []
#int_values.append(len(n_per_layer))
#int_values.append(n_inputs)
#int_values.extend(n_per_layer)
#binary_int_values = bytearray(int_values)
#ascii_binary_int_values = binascii.hexlify(binary_int_values)
#
#float_values = []
#float_values.extend(biases)
#float_values.extend(weights)
#binary_float_values = bytearray()
#for value in float_values:
#    binary_float_values += bytearray(struct.pack("<f", value))
#ascii_binary_float_values = binascii.hexlify(binary_float_values)
#
#ascii_binary_values = ascii_binary_int_values + ascii_binary_float_values

# Write file
with open('snn_config/network.cpp', 'w') as file:

    # HEADER
    file.write('#include "network.h"\n')

    #file.write('unsigned const char network_bin[] = {\n\t',)
    #bytes_in_row = 0
    #for i in range(int(len(ascii_binary_values)/2)):
    #    file.write('0x')
    #    file.write(chr(ascii_binary_values[2*i]))
    #    file.write(chr(ascii_binary_values[2*i+1]))
    #    bytes_in_row += 1
    #    # Avoid ',' in last iteration
    #    if(i != int(len(ascii_binary_values)/2)-1):
    #        file.write(', ') 
    #        if(bytes_in_row == BYTES_PER_ROW):
    #            file.write('\n\t')
    #            bytes_in_row = 0
    #
    #file.write('};')
    #
    #file.write('\n\n')
    #file.write('const int network_bin_len = ')
    #file.write(str(len(ascii_binary_values)))
    #file.write(';')

    # N_INPUTS
    file.write('const uint32_t n_inputs = ')
    file.write(str(n_inputs))
    file.write(';\n')

    # N_OUTPUTS
    file.write('const uint32_t n_outputs = ')
    file.write(str(n_outputs))
    file.write(';\n')

    # N_PER_LAYER
    file.write('uint32_t n_per_layer [] = {')
    idx = 0
    for n in n_per_layer:
        file.write(str(n))
        idx += 1
        if (idx != len(n_per_layer)):
            file.write(', ')
    file.write('};\n')

    # N_LAYERS
    file.write('const uint32_t n_layers = ')
    file.write(str(len(n_per_layer)))
    file.write(';\n')

    # WEIGHTS
    file.write('float weights [] = {\n\t')
    values_per_row = 0
    idx = 0
    for weight in weights:
        file.write('{:20.17f}'.format(weight))
        idx += 1
        values_per_row += 1
        if (idx != len(weights)):
            file.write(', ')
            if(values_per_row == VALUES_PER_ROW):
                file.write('\n\t')
                values_per_row = 0
    file.write('};\n')

    # N_WEIGHTS
    file.write('const uint32_t n_weights = ')
    file.write(str(len(weights)))
    file.write(';\n')

    # BIASES
    file.write('float biases [] = {\n\t')
    values_per_row = 0
    idx = 0
    for bias in biases:
        file.write('{:20.17f}'.format(bias))
        values_per_row += 1
        idx += 1
        if (idx != len(biases)):
            file.write(', ')
            if(values_per_row == VALUES_PER_ROW):
                file.write('\n\t')
                values_per_row = 0
    file.write('};\n')

    # N_BIASES
    file.write('const uint32_t n_biases = ')
    file.write(str(len(biases)))
    file.write(';\n')
