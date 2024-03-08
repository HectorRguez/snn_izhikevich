# Documentation source https://ohwr.org/project/soc-course/wikis/Xilinx-Software-Command-Line-Tool-(XSCT)

# Set workspace
setws vitis/ws

# Create an empty platform
platform create -name snn_izhikevich_pl -hw vivado/snn_hw.xsa
# Specifying an output directory prevents Vitis from finding the platform on the GUI file explorer (Xilinx forum)
# -out ./vitis/ws

# Create the domain
domain create\
    -name snn_izhikevich_dom \
    -os standalone \
    -proc ps7_cortexa9_0

# Build the platform
platform generate

# Create application project inside a system
app create \
    -name snn_izhikevich_app\
    -platform snn_izhikevich_pl\
    -lang c++\
    -template "Empty Application (C++)"\
    -domain snn_izhikevich_dom

# Import sources
importsources\
    -name snn_izhikevich_app\
    -path ./vitis/src/

importsources\
    -name snn_izhikevich_app\
    -path ./network

# Build the application 
app build \
    -name snn_izhikevich_app
