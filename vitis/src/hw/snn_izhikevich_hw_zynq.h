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

static int hw_setup();
static int hw_setup_dma(XAxiDma *axiDma, uint32_t deviceId, uint8_t rxInterrupt, uint8_t txInterrupt);
static int hw_setup_interrupt(XScuGic *intrCtlr);
static void hw_hls_isr(void *instancePtr);
static void hw_dma_rx_isr(void *instancePtr);
static void hw_dma_tx_isr(void *instancePtr);
static void hw_snn_izikevich_start();


#endif /* _SNN_IZIKEVICH_HW_ZYNQ_H_ */