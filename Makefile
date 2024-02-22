.PHONY: load_vivado_environmnent 

# All
all: load_vivado_environmnent 

# Targets 
load_vivado_environmnent:
	@echo "loading vivado environment variables"
	call C:/Xilinx/Vivado/2023.1/settings64.bat && vivado
	@echo "executing vivado"