# Variables
VIVADO_SETTINGS := C:/Xilinx/Vivado/2023.1/settings64.bat


.PHONY: run_vivado

# All
all: create_bd 

run_vivado: 
	@call $(VIVADO_SETTINGS) && \
	vivado -mode batch -nojournal -nolog -source $(SOURCE)

create_bd: design1.bd

# Dependencies
design1.bd: block_design.tcl
	$(MAKE) run_vivado SOURCE= block_design.tcl