# Izhikevich Spiked Neural Network
This repository automates the workflow to create the hardware platform required to use a spiking neural network (SNN) **hardware accelerator** on the Vitis IDE. The SNN computes neuron firings based on the Izhikevich neuron model, which is more biologically accurate than the commonly used Integrate and Fire (I&F) SNNs. This approach is more computationally intensive, which justifies the creation of this project. 

Thus far, this repository includes execution automation using **.tcl scripts** of Felipe Galindo's Thesis Project, which has been considerably restructured.

## Software Requirements
* **IDE**: This project has been developed and tested to run con *Vitis HLS*, *Vivado* and *Vitis* on the [2023.1](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2023-1.html) version.
* **OS**: The project has been tested on [Ubuntu 22.04 LTS](https://ubuntu.com/download/desktop).
* **Serial Terminal**: The simulation data is accessible via serial terminal. [Minicom](https://help.ubuntu.com/community/Minicom) is is the recommended text based communications program. It runs as intended with the default configuration.
* **JTAG drivers** can be installed by running the `install_drivers` script that is contained inside the Xilinx install directory `Xilinx/Vivado/2023.1/data/xicom/cable_drivers/lin64/install_script/install_drivers`.
* [GTK - 3.0](https://docs.gtk.org/gtk3/) is required to run [Vitis xsct commands](https://docs.xilinx.com/r/en-US/ug1400-vitis-embedded/XSCT-Commands).
* The configuration file for the Bash shell [bashrc](https://www.gnu.org/software/bash/manual/html_node/Bash-Startup-Files.html) must include as a source the shell script `settings64.sh`, which is inside the Xilinx install directory `Xilinx/Vivado/2023.1`.

## Project Structure
<pre>
├── Makefile
├── README.md
├── snn_config
│   ├── config.h                          # Selects the SNN that will run and the precision type.
│   ├── networks                          # Network specific defines and functions.
│   └── snn_defs.h                        # Common network defines, includes SNN selected in config.h
├── vitis
│   ├── create_project_vitis.tcl          # Script that adds the Vitis sources and creates workspace.
│   ├── run_vitis.tcl                     # Script that executes the Vitis App on the target board.
│   ├── src                               
│   │   ├── hw
│   │   │   ├── snn_izikevich_hw_zynq.h   # Hardware related functions: DMAs, interrupts...
│   │   │   └── zynq                      # Platform automatically generated drivers
│   │   ├── main_zynq.cpp                 # Program entry point
│   │   └── snn_start.h                   # Main functions of the program: init_network, run_network...
│   └── ws                                # [AUTO-GENERATED] Workspace by create_project_vitis.tcl
├── vitis_hls
│   ├── run_hls.tcl                       # Script that adds the Vitis HLS sources.
│   ├── snn_ip                            # [AUTO-GENERATED] SNN IP in Vivado catalog mode.
│   ├── config.ini                        # [AUTO-GENERATED] Specifies the Vitis HLS project config.
│   └── src
│       ├── snn_izhikevich_axi.h          # Functions used to transmit and receive data.
│       ├── snn_izhikevich.h              # Functions used to run the SNN.
│       ├── snn_izhikevich_top.cpp        # Top functions and memories.
│       └── snn_types.h                   # Type definitions specific to Vitis HLS.
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
The **Makefile** automates the execution of all the project scripts, which target *Vitis HLS*, *Vivado* and *Vitis*. 

### Vitis HLS
1. The SNN accelerator is designed in Vitis HLS. The *C* or *C++* source files must be copied to the `vitis_hls/src` folder
2. The file `vitis_hls/run_hls.tcl` will read the source code, set up the top function as the one named `hls_snn_izikevich`, configure the technology and clock rate, which by default are a **xc7z020clg400-1** board with a **40ns** clock. The generated IP will be exported in the *ip_catalog* format. The generated IP can be found on `vitis_hls/snn_ip`

TODO