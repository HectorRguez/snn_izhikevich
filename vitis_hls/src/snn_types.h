#ifndef _SNN_TYPES_H_
#define _SNN_TYPES_H_

#include "../../snn_config/snn_defs.h"

#define AP_INT_MAX_W 				7168 // 7K
#include "ap_int.h"
#include "stdint.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h" // AXI Stream interface configuration

#if PRECISION_TYPE == FIXED_POINT
#include "ap_fixed.h"
#endif


/*****************************************************************************/
/*                            Type's Definitions                             */
/*****************************************************************************/
#if PRECISION_TYPE == FIXED_POINT
typedef ap_ufixed<WEIGHT_BITS, 0, AP_TRN, AP_WRAP> w_dat_t;
typedef ap_ufixed<SYNAPSE_BITS, SYNAPSE_BITS_INT, AP_TRN, AP_WRAP> s_dat_t;
typedef ap_fixed <POTENTIAL_BITS, POTENTIAL_BITS_INT, AP_TRN, AP_WRAP> vu_dat_t;
#elif PRECISION_TYPE == FLOATING_POINT
typedef float 				w_dat_t;
typedef float 				s_dat_t;
typedef float 				vu_dat_t;
#endif
typedef ap_uint<1>			uint1_t;
typedef ap_uint<2>			uint2_t;
typedef ap_uint<3>			uint3_t;

typedef float 				float32_t;
typedef short 				int16_t;
typedef unsigned short 		uint16_t;

/*****************************************************************************/
/*                            Classes and Utilities                          */
/*****************************************************************************/

// AXI-64 object
typedef ap_axis <64,0,0,0> axis64_t; // DATA WIDTH 64, WITH NO OPTIONAL SIGNALS

// HLS stream
typedef hls::stream<axis64_t> hls_stream_64_t;

union float32_uint32_c {
	uint32_t  u32data;
	float32_t f32data;
};

INLINE uint32_t float32_to_uint32(float32_t value) {
	float32_uint32_c c;
	c.f32data = value;
	return c.u32data;
}

INLINE float32_t uint32_to_float32(uint32_t value) {
	float32_uint32_c c;
	c.u32data = value;
	return c.f32data;
}

INLINE uint64_t float32_to_uint64(float32_t value1, float32_t value2) {
	union float32_uint64_c {
		uint64_t  u64data;
		struct {
			float32_t f32data1;
			float32_t f32data2;
		};
	} c;
	c.f32data1 = value1;
	c.f32data2 = value2;
	return c.u64data;
}

INLINE uint64_t uint32_to_uint64(uint32_t value1, uint32_t value2) {
	union uint32_uint64_c {
		uint64_t  u64data;
		struct {
			uint32_t u32data1;
			uint32_t u32data2;
		};
	} c;
	c.u32data1 = value1;
	c.u32data2 = value2;
	return c.u64data;
}

#endif /* _SNN_TYPES_H_ */
