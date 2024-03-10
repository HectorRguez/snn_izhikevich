# Move to the working directory for vitis_hls
cd vitis_hls/

# Create a project
open_project proj -reset

# Add design files
add_files ../snn_config/snn_defs.h
add_files src/snn_izhikevich_axi.h
add_files src/snn_izhikevich_top.cpp
add_files src/snn_izhikevich.h 
add_files src/snn_network.h 
add_files src/snn_types.h 

# Set the top-level function
set_top hls_snn_izikevich

# ########################################################
# Create a solution
open_solution solution -reset 

# Define technology and clock rate
set_part {xc7z020clg400-1}
create_clock -period 40 -name default

# Run Synthesis
csynth_design

# Export for IP catalog
file mkdir snn_ip
export_design -format ip-catalog -output snn_ip
close_project

exit