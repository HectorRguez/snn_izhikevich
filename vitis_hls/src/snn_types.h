#include <ap_fixed.h>
#include <ap_int.h>

//typedef ap_fixed<14,8> fixed_t;
typedef ap_uint<6> uint6_t;
typedef ap_uint<9> uint9_t;
typedef float fixed_t;
typedef ap_uint<64> uint64_t;

// HLS stream
typedef hls::stream<axis64_t> hls_stream_64_t;