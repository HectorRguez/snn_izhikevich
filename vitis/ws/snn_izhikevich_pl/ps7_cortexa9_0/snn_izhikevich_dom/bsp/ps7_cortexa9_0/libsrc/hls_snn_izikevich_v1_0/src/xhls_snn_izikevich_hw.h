// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.1 (64-bit)
// Tool Version Limit: 2023.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x10 : Data signal of ap_return
//        bit 0  - ap_return[0] (Read)
//        others - reserved
// 0x18 : Data signal of state
//        bit 0  - state[0] (Read/Write)
//        others - reserved
// 0x1c : reserved
// 0x20 : Data signal of p_input
//        bit 31~0 - p_input[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 ~
// 0x2f : Memory 'output_indexes' (2 * 32b)
//        Word n : bit [31:0] - output_indexes[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_CTRL             0x00
#define XHLS_SNN_IZIKEVICH_CONTROL_ADDR_GIE                 0x04
#define XHLS_SNN_IZIKEVICH_CONTROL_ADDR_IER                 0x08
#define XHLS_SNN_IZIKEVICH_CONTROL_ADDR_ISR                 0x0c
#define XHLS_SNN_IZIKEVICH_CONTROL_ADDR_AP_RETURN           0x10
#define XHLS_SNN_IZIKEVICH_CONTROL_BITS_AP_RETURN           1
#define XHLS_SNN_IZIKEVICH_CONTROL_ADDR_STATE_DATA          0x18
#define XHLS_SNN_IZIKEVICH_CONTROL_BITS_STATE_DATA          1
#define XHLS_SNN_IZIKEVICH_CONTROL_ADDR_P_INPUT_DATA        0x20
#define XHLS_SNN_IZIKEVICH_CONTROL_BITS_P_INPUT_DATA        32
#define XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_BASE 0x28
#define XHLS_SNN_IZIKEVICH_CONTROL_ADDR_OUTPUT_INDEXES_HIGH 0x2f
#define XHLS_SNN_IZIKEVICH_CONTROL_WIDTH_OUTPUT_INDEXES     32
#define XHLS_SNN_IZIKEVICH_CONTROL_DEPTH_OUTPUT_INDEXES     2

