#ifndef _SNN_TYPES_H_
#define _SNN_TYPES_H_

#include "../snn_config.h"
#include "snn_env.h"
#include "snn_network.h"

#ifdef RUN_HW_VERSION
#include "stdint.h"

#if RUN_TYPE == TYPE_HLS
#define AP_INT_MAX_W 				7168 // 7K
#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h" // AXI Stream interface configuration
#endif

#if PRECISION_TYPE == FIXED_POINT
#include "ap_fixed.h"
#endif

#endif /* RUN_HW_VERSION */


/*****************************************************************************/
/*                            Type's Definitions                             */
/*****************************************************************************/

/* RUN_HW_VERSION */
#ifdef RUN_HW_VERSION

// Fixed sizes
/*#define VU_WIDTH		32
#define VU_INT			10
#define VU_FRAC 		(VU_WIDTH - VU_INT - 1)
#define S_WIDTH			16
#define S_INT			5
#define S_FRAC 			(S_WIDTH - S_INT)*/


typedef float 					  float32_t;
typedef short 					  int16_t;
typedef unsigned short 			  uint16_t;


#ifdef DEFINE_INT32
typedef int 					  int32_t;
typedef unsigned int 			  uint32_t;
#endif

// HLS
#if RUN_TYPE == TYPE_HLS
typedef ap_uint<1>				  uint1_t;
typedef ap_uint<2>				  uint2_t;
typedef ap_uint<3>				  uint3_t;

#if PRECISION_TYPE == FIXED_POINT
typedef ap_ufixed<WEIGHT_BITS, 0, AP_TRN, AP_WRAP> w_dat_t;
typedef ap_ufixed<SYNAPSE_BITS, SYNAPSE_BITS_INT, AP_TRN, AP_WRAP> s_dat_t;
typedef ap_fixed <POTENTIAL_BITS, POTENTIAL_BITS_INT, AP_TRN, AP_WRAP> vu_dat_t;
#elif PRECISION_TYPE == FLOATING_POINT
typedef float 					  w_dat_t;
typedef float 					  s_dat_t;
typedef float 					  vu_dat_t;
#endif


// ZYNQ
#elif RUN_TYPE == TYPE_ZYNQ
typedef bool       		    	  uint1_t;
typedef char  					  uint2_t;
typedef char     		          uint3_t;
typedef float 					  w_dat_t;
typedef float 					  s_dat_t;
typedef float 					  vu_dat_t;
#endif

#endif /* RUN_HW_VERSION */

// SW version
typedef char uint1_sw_t;
typedef float w_dat_sw_t;
typedef float s_dat_sw_t;
typedef float vu_dat_sw_t;

/*****************************************************************************/
/*                            Classes and Utilities                          */
/*****************************************************************************/

#ifdef RUN_HW_VERSION

union float32_uint32_c {
	uint32_t  u32data;
	float32_t f32data;
};

// HLS
#if RUN_TYPE == TYPE_HLS

// HLS stream
#ifdef SIM_NATIVE_HLS_STREAM
typedef ap_axis <64,1,1,1> axis64_t; // DATA WIDTH 64, TUSER WIDTH 1, TID WIDTH 1, TDEST 1
typedef hls::stream<axis64_t> hls_stream_64_t;
#else
class hls_stream_64_t {
  public:
	uint64_t wr_idx, rd_idx;
	uint64_t *ptr;
	hls_stream_64_t(uint64_t *addr) { wr_idx = 0; rd_idx = 0; ptr = addr; }
	ap_axis <64,1, 1, 1> read() { axis64_t data; data.data = ptr[rd_idx++]; return data; }
	void write(ap_axis <64,1, 1, 1> value) { ptr[wr_idx++] = value.data; }
};
#endif /* HLS stream */

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

#elif RUN_TYPE == TYPE_ZYNQ
inline uint32_t float32_to_uint32(float32_t value) {
	float32_uint32_c c;
	c.f32data = value;
	return c.u32data;
}

inline float32_t uint32_to_float32(uint32_t value) {
	float32_uint32_c c;
	c.u32data = value;
	return c.f32data;
}

inline uint64_t float32_to_uint64(float32_t value1, float32_t value2) {
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

inline uint64_t uint32_to_uint64(uint32_t value1, uint32_t value2) {
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

#endif


#if PRECISION_TYPE == FIXED_POINT
#define norm_weight(weight)	(weight == 0 ? 0 : ((weight < 0.0004883? 0.0004883 : weight) * WEIGHT_SCALE))
#elif PRECISION_TYPE == FLOATING_POINT
#define norm_weight(weight)	(weight)
#endif /* PRECISION_TYPE */

#endif /* RUN_HW_VERSION */

#endif /* _SNN_TYPES_H_ */
