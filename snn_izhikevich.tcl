# Add source files
source "block_design.tcl"
source "add_hls_ip.tcl"


# Define the output directory
set outputDir ./outputs
file mkdir $outputDir

# Configure the project
create_project -in_memory -part xc7z020clg400-1

# Add the hls snn to the IP Catalog
tool_add_xact "hls_snn\component.xml"

# Create the block design
create_root_design ""

# Create the wrapper
make_wrapper -files [get_files  ./bd/mb_ex_1/mb_ex_1.bd] -top
read_vhdl  ./bd/mb_ex_1/hdl/mb_ex_1_wrapper.vhd

# Read constraints - Not needed

#If the block design does not have the output products generated, generate the output products needed for synthesis and implementation runs
set_property synth_checkpoint_mode None [get_files ./bd/mb_ex_1/mb_ex_1.bd]
generate_target all [get_files ./bd/mb_ex_1/mb_ex_1.bd]

#Run synthesis and implementation
synth_design -top mb_ex
opt_design
place_design
route_design
write_bitstream mb_ex.bit

#Export the implemented hardware system to the Vitis environment
write_hw_platform -fixed -force -file ./mb_ex.xsa