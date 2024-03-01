# Izhikevich Spiked Neural Network
This repository automates the workflow to create the hardware platform required to use a spiking neural network (SNN) **hardware accelerator** on the Vitis IDE. The SNN computes neuron firings based on the Izhikevich neuron model, which is more biologically accurate than the commonly used Integrate and Fire (I&F) SNNs.

## Software Requirements
* **IDE**: This project has been developed and tested to run con *Vitis HLS*, *Vivado* and *Vitis* on the [2023.1 version](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2023-1.html).
* **OS**: The project runs on Windows 10 Home, version 22H2, and requires the installation of [Make for Windows](https://gnuwin32.sourceforge.net/packages/make.htm)

## Project Structure
TODO

## How to use
TODO

## Execution flow
The **Makefile** automates the execution of all the project scripts, which target *Vitis HLS*, *Vivado* and *Vitis*. 

### Vitis HLS
1. The SNN accelerator is designed in Vitis HLS. The *C* or *C++* source files must be copied to the `vitis_hls/src` folder
2. The file `vitis_hls/run_hls.tcl` will read the source code, set up the top function as the one named `hls_snn_izikevich`, configure the technology and clock rate, which by default are a **xc7z020clg400-1** board with a **40ns** clock. The generated IP will be exported in the *ip_catalog* format. The generated IP can be found on `vitis_hls/snn_ip`