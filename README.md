# Izhikevich Spiked Neural Network
This repository automates the workflow to create the hardware platform required to use a spiking neural network (SNN) **hardware accelerator** on the Vitis IDE. The SNN computes neuron firings based on the Izhikevich neuron model, which is more biologically accurate than the commonly used Integrate and Fire (I&F) SNNs.

Thus far, this repository includes execution automation using **.tcl scripts** of Felipe Galindo's Thesis Project, which has been considerably restructured.

## Table of contents
- [Software requirements](#software-requirements)
- [Getting started](#getting-started)
- [Project structure](#getting-started)
- [Execution flow](#execution-flow)
- [HW Architecture](#hw-architecture)

## Software requirements
* **IDE**: This project has been developed and tested to run con *Vitis HLS*, *Vivado* and *Vitis* on the [2023.1](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2023-1.html) and [2022.2](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2022-2.html) [^1] [^2]versions.
* **OS**: The project has been tested on [Ubuntu 22.04 LTS](https://ubuntu.com/download/desktop).

* **Serial Terminal**: The execution data is accessible via serial terminal. The default Vitis terminal can be used after installing the necessary drivers, but [Minicom](https://help.ubuntu.com/community/Minicom) can be run directly with the default configuration.

* **JTAG drivers**: Can installed by following [this tutorial](https://support.xilinx.com/s/question/0D52E00006iHmaUSAS/how-to-install-jtag-cable-driver-in-ubuntu16045?language=en_US).

* [GTK - 3.0](https://docs.gtk.org/gtk3/) is required to run [Vitis xsct commands](https://docs.xilinx.com/r/en-US/ug1400-vitis-embedded/XSCT-Commands), which are used in this project.

* The configuration file for the Bash shell [bashrc](https://www.gnu.org/software/bash/manual/html_node/Bash-Startup-Files.html) must include as a source the shell script that allows the execution of vitis_hls, vivado and vitis from the terminal. This was discussed on [this thread](https://support.xilinx.com/s/question/0D52E00006hpO2CSAU/how-to-start-with-vivado-in-linux?language=en_US)

[^1]: The `block_design.tcl` file was exported automatically from the Vivado 2023.1 GUI. It performs a Version check that must be manually deleted to run it this scripts on the 2022.2 version. 

[^2]: If Vitis 2022.2 reports the following error when loading the .elf file `ERROR : Can't read "map": no such variable when trying to launch application on my target`, a workaround is available on the [Xilinx forums](https://support.xilinx.com/s/article/000034848?language=en_US).


## Getting started
1. **Board selection:** The target device is selected by the `BOARD` variable on the makefile. [^3] This repository has been tested with a *xc7z020clg400-1* FPGA. 

2. **Network selection:** To select the network, update the `ORIGIN NETWORK` variable on the makefile. 
The network topology and the different weights and biases are stored in a serialized Python dictionary. Please refer to [this repository](https://github.com/des-cei/gaussianReceptiveFieldCalculator) for examples on how to use PyTorch to train and store networks. 

3. **Data selection:** The execution data is indicated by the `ORIGIN_DATA` variable on the makefile. Data is assumed to be normalized, and is stored in a csv format. 

3. **Generating Vitis HLS IP, the HW platform and the Vitis Workspace** After selecting the board and network, please execute: ```make```. The default target generates the snn IP, exports the hardware and creates a new Vitis workspace inside `Vitis/ws`.

4. **Running the network:**  The generated workspace can be opened directly with Vitis and can be executed directly to the target board.

[^3] Other boards with different processing systems might require updating the block design. It is generated by ```make create_bd```, which must be executed once the accelerator IP has been created by ```make create_ip```. To use a different design, which might be necessary for boards with different processing system characteristics, please open the generated block design `vivado/block_design/block_design.bd`, update it and export it as a tcl script, overwriting the original `vivado/block_design.tcl`.

## Project Structure

<pre>
├── Makefile
├── README.md
├── snn_config
│   ├── databases                         # Input data and labels
│   ├── networks                          # Serialized network weights and biases
│   ├── scripts                           # Transform data and network to C sources
│   ├── data.c                            # [AUTO-GENERATED] Data source file
│   ├── data.h                            # Data header
│   ├── network.c                         # [AUTO-GENERATED] Network source file
│   ├── network.h                         # Network header
│   └── snn_defs.h                        # Network dimensions for memory allocation, train/test division
├── vitis
│   ├── create_project_vitis.tcl          # Script that adds the Vitis sources and creates workspace.
│   ├── run_vitis.tcl                     # Script that executes the Vitis App on the target board.
│   ├── src                               
│   │   ├── hw
│   │   │   ├── snn_izikevich_hw_zynq.h   # Hardware functions to configure and execute the network
│   │   │   └── zynq                      # Platform drivers
│   │   ├── aux_func.cpp                  # Auxiliary functions to rate code and measure execution time
│   │   ├── aux_func.h                    # Auxiliary functions header file
│   │   ├── main_zynq.cpp                 # Executes both networks and prints results
│   │   ├── network_func.cpp              # Software functions to configure and execute the network
│   │   ├── network_func.h                # Software network functions header file
│   │   ├── types.cpp                     # Type conversions
│   │   └── types.h                       # Custom types, type conversion header file
│   └── ws                                # [AUTO-GENERATED] Workspace with the generated project
├── vitis_hls
│   ├── run_hls.tcl                       # Script that adds the Vitis HLS sources.
│   ├── snn_ip                            # [AUTO-GENERATED] SNN IP in Vivado catalog mode.
│   ├── config.ini                        # [AUTO-GENERATED] Vitis HLS project config.
│   └── src
│       ├── snn_izhikevich_top.cpp        # Network execution code for HLS.
│       └── snn_types.h                   # Custom type definitions.
└── vivado
    ├── block_design.tcl                  # Block design exported from the Vivado GUI.
    ├── create_bd.tcl                     # Configures and exports the design defined in block_design.
    ├── synth.tcl                         # Script that synthesizes the exported block design.
    ├── place_and_route.tcl               # Script that places and routes the synthesized design.
    ├── export_hw.tcl                     # Script that exports the design.
    ├── checkpoints                       # [AUTO-GENERATED] Checkpoints for synth, opt,place, ...
    ├── snn_hw.bit                        # [AUTO-GENERATED] Design bitstream.
    ├── snn_hw.xsa                        # [AUTO-GENERATED] Design platform (includes the bitstream).
    └── block_design                      # [AUTO-GENERATED] Block design exported by create_bd.
           
</pre>

## Execution flow
The Makefile automates the execution of all the project scripts, which target *Vitis HLS*, *Vivado* and *Vitis*. 
![Execution flow diagram](https://github.com/des-cei/snn_izhikevich/blob/main/docs/accelerator_diagram?raw=true)


### Vitis HLS
1. The SNN accelerator is designed in Vitis HLS. The *C* or *C++* source files must be copied to the `vitis_hls/src` folder
2. The file `vitis_hls/run_hls.tcl` will read the source code, set up the top function as the one named `hls_snn_izikevich`, configure the technology and clock rate, which by default are a **xc7z020clg400-1** board with a **40ns** clock. The generated IP will be exported in the *ip_catalog* format. The generated IP can be found on `vitis_hls/snn_ip`

*This section is being worked on*

## HW architecture