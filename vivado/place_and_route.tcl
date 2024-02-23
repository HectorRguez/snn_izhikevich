# Read synthezised design
open_checkpoint vivado/checkpoints/synth.dcp

# Placing Design
place_design
write_checkpoint -force vivado/checkpoints/place.dcp

# Routing Design
route_design

# Saving Run
write_checkpoint -force vivado/checkpoints/route.dcp