# Configure the project
create_project -in_memory -part xc7z020clg400-1

# Read the previously created block design
read_bd block_design/block_design.bd

# Create the wrapper
make_wrapper -top -files [get_files block_design/block_design.bd] -fileset . -force

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