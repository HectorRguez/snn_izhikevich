# Configure the board
set_part xc7z020clg400-1

# Add Custom IP to the project IP catalog
set_property ip_repo_paths vivado/hls_snn [current_fileset]
update_ip_catalog

# Read the previously created block design
read_bd block_design/block_design.bd
report_ip_status

# Create the wrapper
make_wrapper -top -files [get_files block_design.bd] -force
read_verilog block_design/hdl/block_design_wrapper.v

#If the block design does not have the output products generated, generate the output products needed for synthesis and implementation runs
generate_target all [get_files block_design/block_design.bd]

#Run synthesis and implementation
synth_design -top block_design_wrapper
opt_design
place_design
route_design
write_bitstream -force snn_hw.bit

#Export the implemented hardware system to the Vitis environment
write_hw_platform -fixed -force -include_bit -file snn_hw.xsa