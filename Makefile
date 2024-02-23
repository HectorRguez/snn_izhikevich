# Variables
VIVADO_SETTINGS := C:/Xilinx/Vivado/2023.1/settings64.bat
RUN_VIVADO:= @call $(VIVADO_SETTINGS) && vivado -mode batch -nojournal -nolog

# Phony targets
.PHONY: run_vivado clean

# Default target
all: create_bd synth place_and_route export_hw clean

# Targets
create_bd: vivado/block_design

synth: vivado/checkpoints/opt.dcp

place_and_route : vivado/checkpoints/route.dcp

export_hw : snn_hw.xsa

# Dependencies
vivado/block_design: vivado/create_bd.tcl hls_snn_ip
	@echo "---------------- Generating block design ----------------"
	@$(RUN_VIVADO) -source vivado/create_bd.tcl

vivado/checkpoints/opt.dcp: vivado/block_design
	@echo "---------------- Synthesizing ----------------"
	@$(RUN_VIVADO) -source vivado/synth.tcl

vivado/checkpoints/route.dcp: vivado/checkpoints/synth.dcp
	@echo "---------------- Place and route ----------------"
	@$(RUN_VIVADO) -source vivado/place_and_route.tcl

snn_hw.xsa: vivado/checkpoints/route.dcp
	@echo "---------------- Saving platform ----------------"
	@$(RUN_VIVADO) -source vivado/export_hw.tcl

# Delete temporal project files
clean:
	@echo "Removing temporal files"
	@if exist .srcs rmdir /s /q .srcs
	@if exist .srcs rmdir /s /q .Xil
	@if exist .srcs rmdir /s /q NA