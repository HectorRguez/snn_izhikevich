################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/zynq/platform.c 

OBJS += \
./src/hw/zynq/platform.o 

C_DEPS += \
./src/hw/zynq/platform.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/zynq/%.o: ../src/hw/zynq/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I/home/hector/Desktop/TFM/automate_snn_hls/snn_izhikevich/vitis/ws/snn_izhikevich_pl/export/snn_izhikevich_pl/sw/snn_izhikevich_pl/snn_izhikevich_dom/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


