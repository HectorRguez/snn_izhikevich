# Configure the project
create_project -in_memory -part xc7z020clg400-1


# Create the wrapper
make_wrapper -files [get_files block_design.bd] -fileset -top
read_verilog block_design_wrapper.v

#If the block design does not have the output products generated, generate the output products needed for synthesis and implementation runs
generate_target all [get_files block_design.bd]

#Run synthesis and implementation
synth_design -top block_design_wrapper
opt_design
place_design
route_design
write_bitstream -force snn_hw.bit

#Export the implemented hardware system to the Vitis environment
write_hw_platform -fixed -force -include_bit -file snn_hw.xsa