#ifndef _SNN_TYPES_H_
#define _SNN_TYPES_H_

#include "stdint.h"
#include "snn_network_defs.h"

/*****************************************************************************/
/*                            Type's Definitions                             */
/*****************************************************************************/

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


typedef bool       		    	  uint1_t;
typedef char  					  uint2_t;
typedef char     		          uint3_t;
typedef float 					  w_dat_t;
typedef float 					  s_dat_t;
typedef float 					  vu_dat_t;


// SW version
typedef char uint1_sw_t;
typedef float w_dat_sw_t;
typedef float s_dat_sw_t;
typedef float vu_dat_sw_t;

/*****************************************************************************/
/*                            Classes and Utilities                          */
/*****************************************************************************/


union float32_uint32_c {
	uint32_t  u32data;
	float32_t f32data;
};


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


#if PRECISION_TYPE == FIXED_POINT
#define norm_weight(weight)	(weight == 0 ? 0 : ((weight < 0.0004883? 0.0004883 : weight) * WEIGHT_SCALE))
#elif PRECISION_TYPE == FLOATING_POINT
#define norm_weight(weight)	(weight)
#endif /* PRECISION_TYPE */

#endif /* _SNN_TYPES_H_ */
