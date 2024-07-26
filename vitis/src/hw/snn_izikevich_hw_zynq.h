#ifndef _SNN_IZIKEVICH_HW_ZYNQ_H_
#define _SNN_IZIKEVICH_HW_ZYNQ_H_

#include <stdint.h>

#include "xhls_snn_izikevich.h"
#include "xaxidma.h"
#include "xscugic.h"
#include "xparameters.h"

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
 *                                Variables      		                     *
 *****************************************************************************/

// Flags
volatile uint32_t status, returnResult, processingDone, rxDone, intError;
volatile uint32_t txDone[] = {0, 0, 0, 0};

// HLS instances
static XHls_snn_izikevich hlsInstance;
static XAxiDma axiDma0;
static XAxiDma axiDma1;
static XAxiDma axiDma2;
static XAxiDma axiDma3;
static XScuGic intrCtlr;

// DMA arrays
uint32_t dmaRegBase[] =  {0, 0, 0, 0};
uint32_t dmaDeviceId[] =  { DMA0_DEVICE_ID, DMA1_DEVICE_ID, DMA2_DEVICE_ID, DMA3_DEVICE_ID };
XAxiDma *dmaDeviceIns[] =  { &axiDma0, &axiDma1, &axiDma2, &axiDma3 };

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

/*****************************************************************************
 *                              Setup Functions    		                     *
 *****************************************************************************/

static int hw_setup() {

	XHls_snn_izikevich_Config *configInstance;

	// Look Up the device configuration
	configInstance = XHls_snn_izikevich_LookupConfig(HLS_DEVICE_ID);
	if (!configInstance) {
		printf("HLS ERORR: Lookup of accelerator configuration failed.\n\r");
		return XST_FAILURE;
	}

	// Initialize the Device
	status = XHls_snn_izikevich_CfgInitialize(&hlsInstance, configInstance);
	if (status != XST_SUCCESS) {
		printf("HLS ERORR: Could not initialize accelerator.\n\r");
		return XST_FAILURE;
	}

	// Disable auto start
	XHls_snn_izikevich_DisableAutoRestart(&hlsInstance);

	// Setup interrupts
	status = hw_setup_interrupt(&intrCtlr);
	if (status != XST_SUCCESS) {
		printf("HLS ERORR: Could not configure interrupts.\n\r");
		return XST_FAILURE;
	}

	// Setup  DMAs
	for(uint32_t i = 0; i < AXI_WEIGHTS_PORTS; i++) {
		status = hw_setup_dma(dmaDeviceIns[i], dmaDeviceId[i], (i == 0), true);
		if (status != XST_SUCCESS) {
			printf("HLS ERORR: Could not configure DMA%ld.\n\r", i);
			return XST_FAILURE;
		}
		dmaRegBase[i] = dmaDeviceIns[i]->RegBase;
	}

	// Checking readiness of device
	if (!XHls_snn_izikevich_IsReady(&hlsInstance))
		return XST_FAILURE;

	return XST_SUCCESS;
}

static int hw_setup_dma(XAxiDma *axiDma, uint32_t deviceId, uint8_t rxInterrupt, uint8_t txInterrupt)
{
	XAxiDma_Config *config;

	config = XAxiDma_LookupConfig(deviceId);
	if (!config) {
		printf("HLS ERROR: No config found for DMA%ld\r\n", deviceId);
		return XST_FAILURE;
	}

	status = XAxiDma_CfgInitialize(axiDma, config);
	if (status != XST_SUCCESS) {
		printf("HLS ERROR: Initialization failed %ld\r\n", status);
		return XST_FAILURE;
	}

	if(XAxiDma_HasSg(axiDma)) {
		printf("HLS ERROR: Device configured as SG mode \r\n");
		return XST_FAILURE;
	}

	// Reset DMA
	XAxiDma_Reset(axiDma);
	while (!XAxiDma_ResetIsDone(axiDma));

	// Disable interrupts at the beginning
	XAxiDma_IntrDisable(axiDma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(axiDma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);
	if (rxInterrupt != 0) XAxiDma_IntrEnable(axiDma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	if (txInterrupt != 0) XAxiDma_IntrEnable(axiDma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

	return XST_SUCCESS;
}

static int hw_setup_interrupt(XScuGic *intrCtlr) {
	// Initialize the interrupt controller driver
	int result;
	XScuGic_Config *pCfg = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (pCfg == NULL){
		print("Interrupt Configuration Lookup Failed\n\r");
		return XST_FAILURE;
	}
	result = XScuGic_CfgInitialize(intrCtlr, pCfg, pCfg->CpuBaseAddress);
	if(result != XST_SUCCESS){
		return result;
	}

	// Set priorities
	XScuGic_SetPriorityTriggerType(intrCtlr, INTR_DMA0_RX_ID, 0xA0, 0x3);
	XScuGic_SetPriorityTriggerType(intrCtlr, INTR_DMA0_TX_ID, 0xA0, 0x3);
	XScuGic_SetPriorityTriggerType(intrCtlr, INTR_DMA1_TX_ID, 0xA0, 0x3);
	XScuGic_SetPriorityTriggerType(intrCtlr, INTR_DMA2_TX_ID, 0xA0, 0x3);
	XScuGic_SetPriorityTriggerType(intrCtlr, INTR_DMA3_TX_ID, 0xA0, 0x3);

	// Connect the Adder ISR's
	result = XScuGic_Connect(intrCtlr, INTR_HLS_ID, (Xil_InterruptHandler)hw_hls_isr, &hlsInstance);
	if(result != XST_SUCCESS) return result;

	result = XScuGic_Connect(intrCtlr, INTR_DMA0_RX_ID, (Xil_InterruptHandler)hw_dma_rx_isr, &axiDma0);
	if(result != XST_SUCCESS) return result;

	result = XScuGic_Connect(intrCtlr, INTR_DMA0_TX_ID, (Xil_InterruptHandler)hw_dma_tx_isr, &axiDma0);
	if(result != XST_SUCCESS) return result;

	result = XScuGic_Connect(intrCtlr, INTR_DMA1_TX_ID, (Xil_InterruptHandler)hw_dma_tx_isr, &axiDma1);
	if(result != XST_SUCCESS) return result;

	result = XScuGic_Connect(intrCtlr, INTR_DMA2_TX_ID, (Xil_InterruptHandler)hw_dma_tx_isr, &axiDma2);
	if(result != XST_SUCCESS) return result;

	result = XScuGic_Connect(intrCtlr, INTR_DMA3_TX_ID, (Xil_InterruptHandler)hw_dma_tx_isr, &axiDma3);
	if(result != XST_SUCCESS) return result;

	// Enable interrupts
	XScuGic_Enable(intrCtlr, INTR_HLS_ID);
	XScuGic_Enable(intrCtlr, INTR_DMA0_RX_ID);
	XScuGic_Enable(intrCtlr, INTR_DMA0_TX_ID);
	XScuGic_Enable(intrCtlr, INTR_DMA1_TX_ID);
	XScuGic_Enable(intrCtlr, INTR_DMA2_TX_ID);
	XScuGic_Enable(intrCtlr, INTR_DMA3_TX_ID);

	// Initialize and register the exception handler
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, (void *)intrCtlr);
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}

static void hw_hls_isr(void *instancePtr) {
	int enabled_list;
	int status_list;
	XHls_snn_izikevich *pInstance = (XHls_snn_izikevich *)instancePtr;

	//Disable Global Interrupt
	XHls_snn_izikevich_InterruptGlobalDisable(pInstance);

	//Get list of enabled interrupts & status interrupts
	enabled_list = XHls_snn_izikevich_InterruptGetEnabled(pInstance);
	status_list = XHls_snn_izikevich_InterruptGetStatus(pInstance);

	//Check ap_done created the interrupt
	if((enabled_list & 1) && (status_list & 1)) {
		//Clear the ap_done interrupt
		XHls_snn_izikevich_InterruptClear(pInstance, 1);
		//Set a result status flag
		processingDone = 1;
	}
}

static void hw_dma_tx_isr(void *callback)
{
	uint32_t irqStatus, regBase;
	XAxiDma *pAxiDmaInstance = (XAxiDma *)callback;

	// Read & acknowledge pending interrupts
	irqStatus = XAxiDma_IntrGetIrq(pAxiDmaInstance, XAXIDMA_DMA_TO_DEVICE);
	regBase = (*pAxiDmaInstance).RegBase;
	XAxiDma_IntrAckIrq(pAxiDmaInstance, irqStatus, XAXIDMA_DMA_TO_DEVICE);

	// If no interrupt is asserted, we do not do anything
	if (!(irqStatus & XAXIDMA_IRQ_ALL_MASK))
		return;

	// If interrupt and error flag, reset the hardware to recover, and return with no further processing.
	if ((irqStatus & XAXIDMA_IRQ_ERROR_MASK)) {
		intError = 1;

		// Reset DMA
		XAxiDma_Reset(pAxiDmaInstance);
		int TimeOut = 10000;

		while (TimeOut) {
			if (XAxiDma_ResetIsDone(pAxiDmaInstance)) {
				break;
			}

			TimeOut -= 1;
		}

		return;
	}

	// If interrupt is asserted, then set the txDone flag
	if ((irqStatus & XAXIDMA_IRQ_IOC_MASK)) {
		for(uint32_t i = 0; i < AXI_WEIGHTS_PORTS; i++) {
			if (regBase == dmaRegBase[i]) {
				txDone[i] = 1;
				return;
			}
		}
	}
}

static void hw_dma_rx_isr(void *callback)
{
	uint32_t irqStatus;	XAxiDma *pAxiDmaInstance = (XAxiDma *)callback;

	// Read & acknowledge pending interrupts
	irqStatus = XAxiDma_IntrGetIrq(pAxiDmaInstance, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrAckIrq(pAxiDmaInstance, irqStatus, XAXIDMA_DEVICE_TO_DMA);

	// If no interrupt is asserted, we do not do anything
	if (!(irqStatus & XAXIDMA_IRQ_ALL_MASK))
		return;

	// If interrupt and error flag, reset the hardware to recover, and return with no further processing.
	if ((irqStatus & XAXIDMA_IRQ_ERROR_MASK)) {
		intError = 1;

		// Reset DMA
		XAxiDma_Reset(pAxiDmaInstance);
		int TimeOut = 10000;
		while (TimeOut) {
					if (XAxiDma_ResetIsDone(pAxiDmaInstance)) {
						break;
					}

					TimeOut -= 1;
				}


		return;
	}

	// If interrupt is asserted, then set rxDone flag
	if ((irqStatus & XAXIDMA_IRQ_IOC_MASK))
		rxDone++;
}

static void hw_snn_izikevich_start() {
	// Reset flags
	processingDone = 0; rxDone = 0; intError = 0;

	//Enable ap_done as an interrupt source and global interrupts
	XHls_snn_izikevich_InterruptEnable(&hlsInstance, 0x1);
	XHls_snn_izikevich_InterruptGlobalEnable(&hlsInstance);

	//Start the IP
	XHls_snn_izikevich_Start(&hlsInstance);
}

static int hw_send_axi_stream_burst(uint32_t stream_addr[], uint32_t streams_qty, uint32_t bytes_size) {
	uint32_t offset; uint32_t bytes;

	// Cache flushing
	for(uint32_t i = 0; i < streams_qty; i++)
	{
		Xil_DCacheFlushRange(stream_addr[i], bytes_size);
	}

	for(offset = 0; offset < bytes_size; offset += MAX_BURST_BYTES) {

		// Get number of bytes to transmit
		if (offset + MAX_BURST_BYTES < bytes_size) bytes = MAX_BURST_BYTES;
		else bytes = bytes_size - offset;

		// Transmit bytes
		for (uint32_t i = 0; i < streams_qty; i++) {
			// Wait if interrupt flag is not yet completed (except first transfer)
			while(offset > 0 && txDone[i] == 0);
			// Clear interrupt flag
			txDone[i] = 0;

			// Start transfer
			status = XAxiDma_SimpleTransfer(dmaDeviceIns[i], stream_addr[i] + offset, bytes, XAXIDMA_DMA_TO_DEVICE);
			if (status != XST_SUCCESS) {
				printf("HLS ERROR: DMA%ld transfer to HLS block failed at offset %ld\n", i, offset);
				return XST_FAILURE;
			}

			// Check for errors
			if (intError) {
				printf("HLS ERROR: Error processing DMA TX transfer...\n");
				return XST_FAILURE;
			}
		}
	}
	// Wait for last iteration to finish
	for (uint32_t i = 0; i < streams_qty; i++) {
		while (txDone[i] == 0);
		txDone[i] = 0;
	}
	return XST_SUCCESS;
}

static int hw_read_axi_stream_burst(uint32_t stream_addr, uint32_t bytes_size) {

	// Flush cache (if enabled) and transmit bytes
	Xil_DCacheFlushRange(stream_addr, bytes_size);
	status = XAxiDma_SimpleTransfer(&axiDma0, stream_addr, bytes_size, XAXIDMA_DEVICE_TO_DMA);
	if (status != XST_SUCCESS) {
		printf("HLS ERROR: DMA transfer from HLS block failed.\n");
		return XST_FAILURE;
	}

	// Wait for RX completion
	while(rxDone < 1 && !intError);
	if (intError) {
		printf("HLS ERROR: Error processing DMA RX transfer...\n");
		return XST_FAILURE;
	}
	rxDone = 0;

	return XST_SUCCESS;
}

/*****************************************************************************
 *                               HW top Functions    		                 *
 *****************************************************************************/
static int hw_snn_izikevich_config_network(float input_c[MAX_LAYER_SIZE], uint32_t n_inputs, uint32_t n_outputs, uint32_t n_per_layer[MAX_LAYER_COUNT], uint32_t n_layers) {
    
    // Set INIT state
    XHls_snn_izikevich_Set_state(&hlsInstance, STATE_INIT);

	// Start the device
	hw_snn_izikevich_start();

	// Set inputs and outputs
    XHls_snn_izikevich_Write_input_c_Words(&hlsInstance, 0, (uint32_t*)input_c, n_inputs); // CHECK
    XHls_snn_izikevich_Set_n_inputs(&hlsInstance, n_inputs);
    XHls_snn_izikevich_Set_n_outputs(&hlsInstance, n_outputs);

    // Set network topology
    XHls_snn_izikevich_Write_n_per_layer_Words(&hlsInstance, 0, n_per_layer, n_layers); // CHECK
    XHls_snn_izikevich_Set_n_layers(&hlsInstance, n_layers);

	// Check return result for verification
	returnResult = XHls_snn_izikevich_Get_return(&hlsInstance);
	if (returnResult != SUCCESS_OK) {
		printf("HLS ERROR: Expected return result %d and got %ld...\n", SUCCESS_OK, returnResult);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

static int hw_snn_izikevich_run(float* weights, uint32_t n_weights, float* biases, uint32_t n_biases, uint32_t n_inputs, uint32_t n_outputs, uint32_t n_per_layer[MAX_LAYER_COUNT], uint32_t n_layers, bool*output) {
    
    // Generate the input stream
    uint64_t input_stream = [AXI_PORTS][((MAX_LAYER_SIZE*(MAX_LAYER_SIZE+1))*MAX_LAYER_COUNT + AXI_PORTS - 1)/AXI_PORTS]; // Upper division
    uint32_t input_idx = 0, weights_idx = 0, biases_idx = 0;
    uint32_t n_prev_layer = n_inputs;
    for(int i = 0; i < n_layers; i++){
        // Add the corresponding number of biases
        for(int j = 0; j < MAX_LAYER_SIZE; j+=2, input_idx++, biases_idx+=2){
			if(j < n_per_layer[i])
            	*(input_stream + input_idx) = (uint64_t)(biases[bias_idx], biases[biases_idx+1]);
			else
				*(input_stream + input_idx) = 0;
	    }
        // Add the corresponding number of weights
        for(int j = 0; j < MAX_LAYER_SIZE*MAX_LAYER_SIZE; j+=2; input_idx++, biases_idx+=2){
			if(j < n_per_layer[i]*n_prev_layer)
            	*(input_stream +input_idx) = (uint64_t)float32_to_uint64(weights[weights_idx], weights[weights_idx+1]);
			else
				*(input_stream + input_idx) = 0;
		}
        n_prev_layer = n_per_layer[i];
    }

	// Set state
	XHls_snn_izikevich_Set_state(&hlsInstance, STATE_PROCESS);

	// Start the device and read the results
	hw_snn_izikevich_start();

	// Write inputs via AXI-Stream
	uint32_t streams[AXI_PORTS] = { (uint32_t)input_stream[0], (uint32_t)input_stream[1], (uint32_t)input_stream[2], (uint32_t)input_stream[3] };
	hw_send_axi_stream_burst(streams, AXI_PORTS, (n_weights + n_biases + 1) / 2 * sizeof(uint64_t)); // Upper division
	if (status != XST_SUCCESS) {
		printf("HLS ERROR: DMA transfer of %ld streams failed to be transfered.\n", AXI_WEIGHTS_LENGTH);
		return XST_FAILURE;
	}

	// Read outputs via AXI-Stream
	status = hw_read_axi_stream_burst(output, (NUM_STEPS*n_outputs+7) / 8); // Upper division n_bytes
	if (status != XST_SUCCESS) {
		printf("HLS ERROR: DMA transfer from HLS block failed.\n");
		return XST_FAILURE;
	}
	// Wait until it is finished or an error is detected
	while(!processingDone);
	// Check return result for verification
	returnResult = XHls_snn_izikevich_Get_return(&hlsInstance);
	if (returnResult != SUCCESS_OK) {
		printf("HLS ERROR: Expected return result %d and got %ld...\n", SUCCESS_OK, returnResult);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}


#endif /* _SNN_IZIKEVICH_HW_ZYNQ_H_ */
