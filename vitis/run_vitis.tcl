# Documentation source https://ohwr.org/project/soc-course/wikis/Xilinx-Software-Command-Line-Tool-(XSCT)

# Set workspace
setws vitis/ws

# Create an empty platform
platform create -name snn_izhikevich_pl -hw vivado/snn_hw.xsa -out ./vitis/ws

# Activate the platform
platform active snn_izhikevich_pl

# Create the domain
domain create -name snn_izhikevich_dom -os standalone -proc ps7_cortexa9_0

# Build the platform
platform generate

# Create application project inside a system
app create -name snn_izhikevich_app -platform snn_izhikevich_pl -domain snn_izhikevich_dom

# Configure the application in release mode
app config -name snn_izhikevich_app build-config release

# Import sources
importsources -name snn_izhikevich_app -path ./vitis/src/

# Build the application 
app build -name snn_izhikevich_app

