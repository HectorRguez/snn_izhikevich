#ifndef _CONFIG_H
#define _CONFIG_H

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
 *                           User Settings	        	                     *
 *****************************************************************************/
/* Precission type */
#define PRECISION_TYPE          FLOATING_POINT

/* Application type */
#define APP_TYPE				APP_XOR

/* Results */
#define PERSIST_RESULTS

#endif /* _CONFIG_H */