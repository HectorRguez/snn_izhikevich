# Script arguments
if { $argc != 1 } {
    puts "The create_bd script requires the board identifier as an argument."
} 

# Configure the project
create_project -in_memory -part [lindex $argv 0]; # Board name

# Add Custom IP to the project IP catalog
set_property ip_repo_paths vitis_hls/snn_ip [current_fileset]
update_ip_catalog

# Create the block design
create_bd_design -name block_design.bd -dir vivado
source [file join [file dirname [info script]] block_design.tcl]
save_bd_design