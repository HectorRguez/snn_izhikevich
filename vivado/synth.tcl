# Configure the board
set_part xc7z020clg400-1

# Add Custom IP to the project IP catalog
set_property ip_repo_paths vitis_hls/snn_ip [current_fileset]
update_ip_catalog

# Read the previously created block design
read_bd vivado/block_design/block_design.bd
report_ip_status

# Create the wrapper
make_wrapper -top -files [get_files block_design.bd] -force
read_verilog vivado/block_design/hdl/block_design_wrapper.v

#If the block design does not have the output products generated, generate the output products needed for synthesis and implementation runs
generate_target all [get_files vivado/block_design/block_design.bd]

#Run synthesis and implementation
synth_design -top block_design_wrapper

# Save checkpoint
file mkdir vivado/checkpoints
write_checkpoint -force vivado/checkpoints/synth.dcp

# Optimize design
opt_design

# Save checkpoint
write_checkpoint -force vivado/checkpoints/opt.dcp