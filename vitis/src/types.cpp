#include "types.h"

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
    float32_uint64_c c;
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
