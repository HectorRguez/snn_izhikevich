# Izhikevich Spiked Neural Network
This repository automates the workflow to create the hardware platform required to use a spiking neural network (SNN) **hardware accelerator** on the Vitis IDE. The SNN computes neuron firings based on the Izhikevich neuron model, which is more biologically accurate than the commonly used Integrate and Fire (I&F) SNNs.

## Software Requirements
* **IDE**: This project has been developed and tested to run con *Vitis HLS*, *Vivado* and *Vitis* on the [2023.1 version](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2023-1.html).
* **OS**: The project has been tested on [Ubuntu 22.04 LTS](https://ubuntu.com/download/desktop).
* **Serial Terminal**: The simulation data is accessible via serial terminal. [Minicom](https://help.ubuntu.com/community/Minicom) is is the recommended text based communications program.


## Project Structure
<pre>
├── Makefile                                    
├── README.md                                
├── vitis
│   ├── create_project_vitis.tcl         # This script creates the Vitis workspace (App and Platform)
│   ├── run_vitis.tcl                    # This script executes the App in the PYNQ board
│   ├── src                              # C++ files that will be executed on the board CPU
│   └── ws                               
├── vitis_hls
│   ├── run_hls.tcl                      
│   └── src                              
└── vivado                               
    ├── block_design.tcl                 
    ├── create_bd.tcl                    
    ├── export_hw.tcl                    
    ├── place_and_route.tcl              
    └── synth.tcl                        
</pre>
## How to use
1. 
1. Install JTAG drivers `/tools/Xilinx/Vivado/2023.1/data/xicom/cable_drivers/lin64/install_script/install_drivers`

## Execution flow
The **Makefile** automates the execution of all the project scripts, which target *Vitis HLS*, *Vivado* and *Vitis*. 

### Vitis HLS
1. The SNN accelerator is designed in Vitis HLS. The *C* or *C++* source files must be copied to the `vitis_hls/src` folder
2. The file `vitis_hls/run_hls.tcl` will read the source code, set up the top function as the one named `hls_snn_izikevich`, configure the technology and clock rate, which by default are a **xc7z020clg400-1** board with a **40ns** clock. The generated IP will be exported in the *ip_catalog* format. The generated IP can be found on `vitis_hls/snn_ip`