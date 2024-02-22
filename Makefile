# Variables
VIVADO_SETTINGS := C:/Xilinx/Vivado/2023.1/settings64.bat
RUN_VIVADO:= @call $(VIVADO_SETTINGS) && vivado -mode batch -nojournal -nolog
	
# Phony targets
.PHONY: run_vivado clean

# Default target
all: create_bd clean

# Targets
create_bd: block_design

create_hw: snn_hw.xsa

# Dependencies
block_design: create_block_design.tcl
	@echo "Generating block design"
	@$(RUN_VIVADO) -source create_block_design.tcl

snn_hw.xsa: block_design
	@echo "Creating hardware"
	@$(RUN_VIVADO) -source create_hw.tcl

# Delete temporal project files
clean:
	@echo "Removing temporal files"
	@rmdir /s /q .srcs .Xil NA