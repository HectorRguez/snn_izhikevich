#ifndef _SNN_DEFS_H_
#define _SNN_DEFS_H_

// Training data
#define TRAIN_DATA_PROPORTION 0.7f

// Memory size and max loop iteration defines
#define MAX_LAYER_SIZE  16
#define NUM_STEPS       30
#define MAX_LAYER_COUNT 8

// Neuron type
#define NONE 0
#define LIF  1
#define IZHI 2
#define NEURON_MODEL LIF

// Accelerator state machine
#define STATE_INIT			0
#define STATE_PROCESS		1
#define SUCCESS_OK			1

// Interface
#define AXI_PORTS           4
#define TRANSMISSION_SIZE (((MAX_LAYER_SIZE*(MAX_LAYER_SIZE+1)) + AXI_PORTS - 1)/AXI_PORTS)

#endif /* _SNN_DEFS_H_ */