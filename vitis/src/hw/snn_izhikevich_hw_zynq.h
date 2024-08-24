#ifndef _SNN_IZIKEVICH_HW_ZYNQ_H_
#define _SNN_IZIKEVICH_HW_ZYNQ_H_

#include "xhls_snn_izikevich.h"
#include "xaxidma.h"
#include "xscugic.h"
#include "xparameters.h"
#include "xil_printf.h"

#include "../snn_defs.h" 
#include "../types.h"

/*****************************************************************************
 *                          Hardware Definitions      		                 *
 *****************************************************************************/

#define	HLS_DEVICE_ID		XPAR_HLS_SNN_IZIKEVICH_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define DMA0_DEVICE_ID		XPAR_AXI_DMA_0_DEVICE_ID
#define DMA1_DEVICE_ID		XPAR_AXI_DMA_1_DEVICE_ID
#define DMA2_DEVICE_ID		XPAR_AXI_DMA_2_DEVICE_ID
#define DMA3_DEVICE_ID		XPAR_AXI_DMA_3_DEVICE_ID


#define INTR_HLS_ID			XPAR_FABRIC_HLS_SNN_IZIKEVICH_0_INTERRUPT_INTR
#define INTR_DMA0_RX_ID		XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR
#define INTR_DMA0_TX_ID		XPAR_FABRIC_AXI_DMA_0_MM2S_INTROUT_INTR
#define INTR_DMA1_TX_ID		XPAR_FABRIC_AXI_DMA_1_MM2S_INTROUT_INTR
#define INTR_DMA2_TX_ID		XPAR_FABRIC_AXI_DMA_2_MM2S_INTROUT_INTR
#define INTR_DMA3_TX_ID		XPAR_FABRIC_AXI_DMA_3_MM2S_INTROUT_INTR


#define MAX_BURST_BYTES		15 * 1024 // 15K per burst

/*****************************************************************************
 *                                Prototypes    		                     *
 *****************************************************************************/

// "Private" prototypes
int hw_setup_dma(XAxiDma *axiDma, uint32_t deviceId, uint8_t rxInterrupt, uint8_t txInterrupt);
int hw_setup_interrupt(XScuGic *intrCtlr);
void hw_hls_isr(void *instancePtr);
void hw_dma_rx_isr(void *instancePtr);
void hw_dma_tx_isr(void *instancePtr);
void hw_snn_izikevich_start();

// Public prototypes
int hw_setup();
int hw_snn_izikevich_config_network(float input_c[MAX_LAYER_SIZE], uint32_t n_inputs, 
	uint32_t n_outputs, uint32_t n_per_layer[MAX_LAYER_COUNT], uint32_t n_layers);
int hw_snn_izikevich_prepare_weight_bias_stream(float* weights, uint32_t n_weights, 
    float* biases, uint32_t n_biases, uint32_t n_inputs, uint32_t n_per_layer[MAX_LAYER_COUNT], 
    uint32_t n_layers, uint64_t input_stream [AXI_PORTS][TRANSMISSION_SIZE*MAX_LAYER_COUNT/2]);
int hw_snn_izikevich_run(uint64_t input_stream [AXI_PORTS][TRANSMISSION_SIZE*MAX_LAYER_COUNT/2],
    uint32_t n_input_stream, uint32_t n_outputs, bool*output);

#endif /* _SNN_IZIKEVICH_HW_ZYNQ_H_ */