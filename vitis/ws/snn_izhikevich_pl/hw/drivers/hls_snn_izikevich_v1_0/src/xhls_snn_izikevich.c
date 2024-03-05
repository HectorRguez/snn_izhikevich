// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
// Tool Version Limit: 2023.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xhls_snn_izikevich.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XHls_snn_izikevich_CfgInitialize(XHls_snn_izikevich *InstancePtr, XHls_snn_izikevich_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XHls_snn_izikevich_Start(XHls_snn_izikevich *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_CTRL) & 0x80;
    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XHls_snn_izikevich_IsDone(XHls_snn_izikevich *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XHls_snn_izikevich_IsIdle(XHls_snn_izikevich *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XHls_snn_izikevich_IsReady(XHls_snn_izikevich *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XHls_snn_izikevich_EnableAutoRestart(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XHls_snn_izikevich_DisableAutoRestart(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_CTRL, 0);
}

u32 XHls_snn_izikevich_Get_return(XHls_snn_izikevich *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_RETURN);
    return Data;
}
void XHls_snn_izikevich_Set_state(XHls_snn_izikevich *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_STATE_DATA, Data);
}

u32 XHls_snn_izikevich_Get_state(XHls_snn_izikevich *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_STATE_DATA);
    return Data;
}

void XHls_snn_izikevich_Set_p_input(XHls_snn_izikevich *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_P_INPUT_DATA, Data);
}

u32 XHls_snn_izikevich_Get_p_input(XHls_snn_izikevich *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_P_INPUT_DATA);
    return Data;
}

u32 XHls_snn_izikevich_Get_output_indexes_BaseAddress(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE);
}

u32 XHls_snn_izikevich_Get_output_indexes_HighAddress(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_HIGH);
}

u32 XHls_snn_izikevich_Get_output_indexes_TotalBytes(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_HIGH - XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE + 1);
}

u32 XHls_snn_izikevich_Get_output_indexes_BitWidth(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XHLS_SNN_IZIKEVICH_CONTROL_WIDTH_OUTPUT_INDEXES;
}

u32 XHls_snn_izikevich_Get_output_indexes_Depth(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XHLS_SNN_IZIKEVICH_CONTROL_DEPTH_OUTPUT_INDEXES;
}

u32 XHls_snn_izikevich_Write_output_indexes_Words(XHls_snn_izikevich *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_HIGH - XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XHls_snn_izikevich_Read_output_indexes_Words(XHls_snn_izikevich *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_HIGH - XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE + (offset + i)*4);
    }
    return length;
}

u32 XHls_snn_izikevich_Write_output_indexes_Bytes(XHls_snn_izikevich *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_HIGH - XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XHls_snn_izikevich_Read_output_indexes_Bytes(XHls_snn_izikevich *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_HIGH - XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE + offset + i);
    }
    return length;
}

void XHls_snn_izikevich_InterruptGlobalEnable(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_GIE, 1);
}

void XHls_snn_izikevich_InterruptGlobalDisable(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_GIE, 0);
}

void XHls_snn_izikevich_InterruptEnable(XHls_snn_izikevich *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_IER);
    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_IER, Register | Mask);
}

void XHls_snn_izikevich_InterruptDisable(XHls_snn_izikevich *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_IER);
    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_IER, Register & (~Mask));
}

void XHls_snn_izikevich_InterruptClear(XHls_snn_izikevich *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XHls_snn_izikevich_WriteReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_ISR, Mask);
}

u32 XHls_snn_izikevich_InterruptGetEnabled(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_IER);
}

u32 XHls_snn_izikevich_InterruptGetStatus(XHls_snn_izikevich *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XHls_snn_izikevich_ReadReg(InstancePtr->Control_BaseAddress, XHLS_SNN_IZIKEVICH_CONTROL_ADDR_ISR);
}

