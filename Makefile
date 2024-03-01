# Variables
VIVADO_SETTINGS := C:/Xilinx/Vivado/2023.1/settings64.bat
VITIS_HLS_SETTINGS := C:\Xilinx\Vitis_HLS\2023.1\settings64.bat
RUN_VIVADO:= @call $(VIVADO_SETTINGS) && vivado -mode batch -nojournal -nolog
RUN_VITIS_HLS:= @call $(VITIS_HLS_SETTINGS) && vitis_hls 

# Phony targets
.PHONY: clean_hls clean_vivado

# Default target
all: create_ip create_bd synth place_and_route export_hw clean_hls clean_vivado

# Targets
create_ip: vitis_hls/src/*

create_bd: vivado/block_design/block_design.bd

synth: vivado/checkpoints/opt.dcp

place_and_route : vivado/checkpoints/route.dcp

export_hw : vivado/snn_hw.xsa

# Dependencies
vitis_hls/snn_ip/src/*:
	@echo "########### Generating SNN IP ###########"
	@$(RUN_VITIS_HLS) -f vitis_hls/run_hls.tcl
	@powershell -command "Expand-Archive -Force vitis_hls/snn_ip/export.zip vitis_hls/snn_ip"

vivado/block_design/block_design.bd: vivado/create_bd.tcl vitis_hls/snn_ip/*
	@echo "########### Generating block design ###########"
	@$(RUN_VIVADO) -source vivado/create_bd.tcl

vivado/checkpoints/opt.dcp: vivado/block_design/block_design.bd
	@echo "########### Synthesizing ###########"
	@$(RUN_VIVADO) -source vivado/synth.tcl

vivado/checkpoints/route.dcp: vivado/checkpoints/synth.dcp
	@echo "########### Place and route ###########"
	@$(RUN_VIVADO) -source vivado/place_and_route.tcl

snn_hw.xsa: vivado/checkpoints/route.dcp
	@echo "########### Saving platform ###########"
	@$(RUN_VIVADO) -source vivado/export_hw.tcl

# Delete temporal project files
clean_hls : 
	@echo "########### Removing temporal Vitis_HLS ########### "
	@if exist vitis_hls.log del vitis_hls.log
	@if exist "vitis_hls\proj\" rmdir /s /q "vitis_hls\proj\"
	@if exist "vitis_hls\snn_ip\export.zip" del "vitis_hls\snn_ip\export.zip"

clean_vivado:
	@echo "########### Removing temporal Vivado files ########### "
	@if exist .srcs rmdir /s /q .srcs
	@if exist .Xil rmdir /s /q .Xil
	@if exist NA rmdir /s /q NA