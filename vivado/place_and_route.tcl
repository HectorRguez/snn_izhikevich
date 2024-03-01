# Move to the working directory for vitis_hls
cd vivado/

# Read synthezised design
open_checkpoint checkpoints/synth.dcp

# Placing Design
place_design
write_checkpoint -force checkpoints/place.dcp

# Routing Design
route_design

# Saving Run
write_checkpoint -force checkpoints/route.dcp