#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>

/*****************************************************************************/
/*                            Type's Definitions                             */
/*****************************************************************************/
typedef float 				float32_t;
typedef short 				int16_t;
typedef unsigned short 		uint16_t;

/*****************************************************************************/
/*                            Classes and Utilities                          */
/*****************************************************************************/
union float32_uint32_c {
	uint32_t  u32data;
	float32_t f32data;
};

union float32_uint64_c {
	uint64_t  u64data;
	struct {
		float32_t f32data1;
		float32_t f32data2;
	};
};

uint32_t float32_to_uint32(float32_t value);

float32_t uint32_to_float32(uint32_t value);

uint64_t float32_to_uint64(float32_t value1, float32_t value2);

uint64_t uint32_to_uint64(uint32_t value1, uint32_t value2);

#endif /* _TYPES_H_ */
