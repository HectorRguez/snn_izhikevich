# Variables
VIVADO_SETTINGS := C:/Xilinx/Vivado/2023.1/settings64.bat


# Phony targets
.PHONY: run_vivado

# Default target
all: create_bd

# Run Vivado
run_vivado: 
	@call $(VIVADO_SETTINGS) && \
	vivado -mode batch -nojournal -nolog -source $(SOURCE)

create_bd: design1.bd

# Dependencies
design1.bd: block_design.tcl
	$(MAKE) run_vivado SOURCE= block_design.tcl