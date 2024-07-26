#ifndef _SNN_TYPES_H_
#define _SNN_TYPES_H_

/*****************************************************************************/
/*                            Type's Definitions                             */
/*****************************************************************************/
typedef float 				float32_t;
typedef short 				int16_t;
typedef unsigned short 		uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long       uint64_t;

/*****************************************************************************/
/*                            Classes and Utilities                          */
/*****************************************************************************/
union float32_uint32_c {
	uint32_t  u32data;
	float32_t f32data;
};

uint32_t float32_to_uint32(float32_t value) {
	float32_uint32_c c;
	c.f32data = value;
	return c.u32data;
}

float32_t uint32_to_float32(uint32_t value) {
	float32_uint32_c c;
	c.u32data = value;
	return c.f32data;
}

uint64_t float32_to_uint64(float32_t value1, float32_t value2) {
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

uint64_t uint32_to_uint64(uint32_t value1, uint32_t value2) {
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
