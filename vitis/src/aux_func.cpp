#include "aux_func.h"

int read_bin(char file_name[PATH_SIZE], int buffer[NET_BUFFER_SIZE]){
    FILE* fp = NULL;
    fp = fopen(file_name, "rb");
    // Check if the file was opened successfully
    if(fp == NULL){
        printf("ERROR Could not open file\n");
        return(-1);
    }
    int read_values = fread(buffer, sizeof(*buffer), NET_BUFFER_SIZE, fp);
    fclose(fp);
    return read_values;
}

int count_n_biases(int*n_per_layer, int n_layers){
    int n_biases = 0;
    for(int i = 0; i < n_layers; i++){
        n_biases += n_per_layer[i];
    }
    return n_biases;
}

int count_n_weights(int n_in, int*n_per_layer, int n_layers){
    // Parse the weights
    int n_weights = 0, current_layer_n = 0, prev_layer_n = n_in;
    for(int i = 0; i < n_layers; i++){
        current_layer_n = n_per_layer[i];
        n_weights += current_layer_n * prev_layer_n;
        prev_layer_n = current_layer_n; // Next iteration
    }
    return n_weights;
}

int read_csv(char file_name[PATH_SIZE], 
    float buffer[MAX_N_INPUTS*MAX_N_INPUT_VALUES], 
    int*n_lines, int*n_parameters){

    FILE* fp = NULL;
    fp = fopen(file_name, "r");
    // Check if the file was opened successfully
    if(fp == NULL){
        printf("ERROR Could not open file\n");
        return(-1);
    }
    // Read line by line
    int buffer_idx = 0, line_count = 0;
    int parameter_count = 0, prev_parameter_count = -1;
    char line[MAX_LINE_SIZE] = "";
    while(true)
    {
        // Check if we are at the end of the file
        if(feof(fp) != 0) break;

        // Read a line from the file
        char* line_ptr = fgets(line, MAX_LINE_SIZE, fp);
        if(line_ptr == NULL){
            printf("ERROR Could not read line %i\n", line_count);
            return(-1);
        }
        // Read until the end of the line
        while(true){
            // Read a parameter in the line
            int scanned_characters, scanned_success;
            scanned_success = sscanf(line_ptr, "%f%n", 
                &buffer[buffer_idx], &scanned_characters);
            if(scanned_success != 1){
                int value_position = line_ptr-line;
                printf("ERROR Could not read value in position %i in line %i\n", 
                    value_position, line_count);
                return(-1);
            }
            line_ptr += scanned_characters;
            parameter_count++;
            buffer_idx++;

            // Ensure that the there is no overflow in the file buffer
            if(buffer_idx > MAX_N_INPUTS*MAX_N_INPUT_VALUES){
                printf("ERROR Read file is too large,");
                printf("please increase MAX_N_INPUTS or MAX_N_INPUT_VALUES\n");
                return(-1);
            }

            // Skip the comma (or end of the line, end of file, etc)
            char separator = *line_ptr;
            if(separator == ',') line_ptr++; // Next character
            else if(separator == '\n') break; // End of line 
            else if(separator == 0) break; // End of file
            else{
                int value_position = line_ptr-line;
                printf("ERROR Could not interpret character");
                printf("'%c' in position %i in line %i\n",
                    separator, value_position, line_count);
                return(-1);
            }
        }
        if((parameter_count != prev_parameter_count )&&
            (prev_parameter_count != -1)){

            printf("ERROR Read %i parameters on line %i", 
                parameter_count, line_count);
            printf("and %i on line %i\n", prev_parameter_count, line_count-1);
            return(-1);
        }
        prev_parameter_count = parameter_count;
        parameter_count = 0;
        line_count++;
    }
    fclose(fp);
    *n_lines = line_count, *n_parameters = prev_parameter_count;
    return line_count * prev_parameter_count;
}

int normalize_data(float buffer[], int n_lines, int n_parameters){
    float min, max, curr, curr_norm; 
    for(int i = 0; i < n_parameters; i++){  // Last parameter -> Label
        // Find the minimum and maximum value
        min = buffer[i], max = buffer[i];
        for(int j = 1; j < n_lines; j++){
            curr = buffer[j*n_parameters+i];
            min = (curr < min) ? curr : min;
            max = (curr > max) ? curr : max;
        }
        if(max == min) return -1; // Avoid division by zero error

        // Normalize
        for(int j = 0; j < n_lines; j++){
            curr = buffer[j*n_parameters+i];
            curr_norm = (curr - min) / (max - min);
            buffer[j*n_parameters+i] = curr_norm;
        }
    }
    return 0;
}

void parse_in_out(float buffer[MAX_N_INPUTS*MAX_N_INPUT_VALUES], 
    float*in, int*out, int n_lines, int n_parameters){

    int buffer_idx = 0;
    for(int i = 0; i < n_lines; i++){
        for(int j = 0; j < n_parameters-1; j++){ // Last parameter -> Label
            in[i*n_parameters+j] = buffer[buffer_idx++];
        }
        out[i] = (int)buffer[buffer_idx++];
    }
}

int rate_code_result(bool*out_spk, int n_out, int n_steps){
    // Count the number of spikes on each output neuron
    int* absolute_freq = (int*)calloc(n_out, sizeof(int));
    for(int i = 0; i < n_out; i++){
        for(int j = 0; j < n_steps; j++){
            if(out_spk[i*n_steps+j]) absolute_freq[i]++;
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
    free(absolute_freq);

    return (max_freq_idx); 
}