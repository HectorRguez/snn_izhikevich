#ifndef _AUX_FUN_H_
#define _AUX_FUN_H_

// Include standard libraries
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

// PYNQ libraries
#include "xtime_l.h"

// Time defines
#define COUNTS_PER_MS	(COUNTS_PER_SECOND/1000)

// Function prototypes
int normalize_data(float buffer[], int n_lines, int n_parameters);      
int rate_code_result(bool*out_spk, uint32_t n_out, uint32_t n_steps);
void start_clock();
void stop_clock();
void reset_clock();
float get_clock_ms();

#endif /* _AUX_FUN_H_ */