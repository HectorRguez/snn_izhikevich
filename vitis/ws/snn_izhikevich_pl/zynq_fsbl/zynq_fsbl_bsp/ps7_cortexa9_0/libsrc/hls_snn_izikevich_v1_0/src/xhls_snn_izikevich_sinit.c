// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
// Tool Version Limit: 2023.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xhls_snn_izikevich.h"

extern XHls_snn_izikevich_Config XHls_snn_izikevich_ConfigTable[];

XHls_snn_izikevich_Config *XHls_snn_izikevich_LookupConfig(u16 DeviceId) {
	XHls_snn_izikevich_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XHLS_SNN_IZIKEVICH_NUM_INSTANCES; Index++) {
		if (XHls_snn_izikevich_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XHls_snn_izikevich_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XHls_snn_izikevich_Initialize(XHls_snn_izikevich *InstancePtr, u16 DeviceId) {
	XHls_snn_izikevich_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XHls_snn_izikevich_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XHls_snn_izikevich_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

