# Read routed design
open_checkpoint vivado/checkpoints/route.dcp

# Save bitstream separately
write_bitstream -force vivado/snn_hw.bit

#Export the implemented hardware system to the Vitis environment
write_hw_platform -fixed -force -include_bit -file vivado/snn_hw.xsa