# Variables
RUN_VIVADO:= vivado -mode batch -nojournal -nolog

# Phony targets
.PHONY: clean_hls clean_vivado clean_vitis run_app open_vitis

# Default target
all: create_ip clean_hls create_bd synth place_and_route export_hw\
	clean_vivado create_app clean_vitis

# Run application target
run: run_app
	@xsct vitis/run_vitis.tcl

# Open vitis GUI
open_vitis :
	vitis -workspace vitis/ws/

# Secondary targets
create_ip: vitis_hls/snn_ip/component.xml

create_bd: vivado/block_design/block_design.bd

synth: vivado/checkpoints/opt.dcp

place_and_route : vivado/checkpoints/route.dcp

export_hw : vivado/snn_hw.xsa

create_app : vitis/ws/*

# Dependencies
vitis_hls/snn_ip/component.xml : vitis_hls/src/*
	@vitis_hls -f vitis_hls/run_hls.tcl
	@unzip vitis_hls/snn_ip/export.zip -d vitis_hls/snn_ip

vivado/block_design/block_design.bd: vivado/create_bd.tcl \
	vitis_hls/snn_ip/component.xml
	@$(RUN_VIVADO) -source vivado/create_bd.tcl

vivado/checkpoints/opt.dcp: vivado/block_design/block_design.bd
	@$(RUN_VIVADO) -source vivado/synth.tcl

vivado/checkpoints/route.dcp: vivado/checkpoints/synth.dcp
	@$(RUN_VIVADO) -source vivado/place_and_route.tcl

vivado/snn_hw.xsa: vivado/checkpoints/route.dcp
	@$(RUN_VIVADO) -source vivado/export_hw.tcl

vitis/ws/*: vitis/src/* vivado/snn_hw.xsa
	rm -rf vitis/ws
	@xsct vitis/create_project_vitis.tcl


# Delete temporal project files
clean_hls : 
	@rm -f  vitis_hls.log
	@rm -rf vitis_hls/proj/
	@rm -f  vitis_hls/snn_ip/export.zip

clean_vivado:
	@rm -rf .srcs
	@rm -rf .Xil
	@rm -rf NA

clean_vitis:
	@rm -rf .Xil
	@rm -f xrc.log