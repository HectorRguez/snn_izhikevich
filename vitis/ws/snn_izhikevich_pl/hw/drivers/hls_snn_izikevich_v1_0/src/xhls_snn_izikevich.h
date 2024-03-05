// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
// Tool Version Limit: 2023.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XHLS_SNN_IZIKEVICH_H
#define XHLS_SNN_IZIKEVICH_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xhls_snn_izikevich_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XHls_snn_izikevich_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XHls_snn_izikevich;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XHls_snn_izikevich_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XHls_snn_izikevich_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XHls_snn_izikevich_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XHls_snn_izikevich_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XHls_snn_izikevich_Initialize(XHls_snn_izikevich *InstancePtr, u16 DeviceId);
XHls_snn_izikevich_Config* XHls_snn_izikevich_LookupConfig(u16 DeviceId);
int XHls_snn_izikevich_CfgInitialize(XHls_snn_izikevich *InstancePtr, XHls_snn_izikevich_Config *ConfigPtr);
#else
int XHls_snn_izikevich_Initialize(XHls_snn_izikevich *InstancePtr, const char* InstanceName);
int XHls_snn_izikevich_Release(XHls_snn_izikevich *InstancePtr);
#endif

void XHls_snn_izikevich_Start(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_IsDone(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_IsIdle(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_IsReady(XHls_snn_izikevich *InstancePtr);
void XHls_snn_izikevich_EnableAutoRestart(XHls_snn_izikevich *InstancePtr);
void XHls_snn_izikevich_DisableAutoRestart(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_Get_return(XHls_snn_izikevich *InstancePtr);

void XHls_snn_izikevich_Set_state(XHls_snn_izikevich *InstancePtr, u32 Data);
u32 XHls_snn_izikevich_Get_state(XHls_snn_izikevich *InstancePtr);
void XHls_snn_izikevich_Set_p_input(XHls_snn_izikevich *InstancePtr, u32 Data);
u32 XHls_snn_izikevich_Get_p_input(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_Get_output_indexes_BaseAddress(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_Get_output_indexes_HighAddress(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_Get_output_indexes_TotalBytes(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_Get_output_indexes_BitWidth(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_Get_output_indexes_Depth(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_Write_output_indexes_Words(XHls_snn_izikevich *InstancePtr, int offset, word_type *data, int length);
u32 XHls_snn_izikevich_Read_output_indexes_Words(XHls_snn_izikevich *InstancePtr, int offset, word_type *data, int length);
u32 XHls_snn_izikevich_Write_output_indexes_Bytes(XHls_snn_izikevich *InstancePtr, int offset, char *data, int length);
u32 XHls_snn_izikevich_Read_output_indexes_Bytes(XHls_snn_izikevich *InstancePtr, int offset, char *data, int length);

void XHls_snn_izikevich_InterruptGlobalEnable(XHls_snn_izikevich *InstancePtr);
void XHls_snn_izikevich_InterruptGlobalDisable(XHls_snn_izikevich *InstancePtr);
void XHls_snn_izikevich_InterruptEnable(XHls_snn_izikevich *InstancePtr, u32 Mask);
void XHls_snn_izikevich_InterruptDisable(XHls_snn_izikevich *InstancePtr, u32 Mask);
void XHls_snn_izikevich_InterruptClear(XHls_snn_izikevich *InstancePtr, u32 Mask);
u32 XHls_snn_izikevich_InterruptGetEnabled(XHls_snn_izikevich *InstancePtr);
u32 XHls_snn_izikevich_InterruptGetStatus(XHls_snn_izikevich *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
