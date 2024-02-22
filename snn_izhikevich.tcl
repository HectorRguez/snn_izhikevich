# Configure the project
create_project -in_memory -part xc7z020clg400-1

# Add Custom IP to the project
set_property ip_repo_paths "hls_snn" [current_fileset]
update_ip_catalog

# Create the block design
source [file join [file dirname [info script]] "block_design.tcl"]

# Create the wrapper
make_wrapper -files [get_files ./srcs/sources_1/bd/design1/design1.bd] -top
read_verilog ./gen/sources_1/bd/design1/design1_wrapper.v


#If the block design does not have the output products generated, generate the output products needed for synthesis and implementation runs
generate_target all [get_files "design1.bd"]

#Run synthesis and implementation
synth_design -top design_1_wrapper
opt_design
#Write debugging file to use the ILAs
write_debug_probes -force 6_ilas.ltx
place_design
route_design
write_bitstream -force snn_6_ilas.bit

#Export the implemented hardware system to the Vitis environment
write_hw_platform -fixed -force -file ./snn_6_ilas.xsa