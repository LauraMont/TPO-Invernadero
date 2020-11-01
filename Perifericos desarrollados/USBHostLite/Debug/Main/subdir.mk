################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Main/cr_startup_lpc176x.c \
../Main/usbhost_main.c 

OBJS += \
./Main/cr_startup_lpc176x.o \
./Main/usbhost_main.o 

C_DEPS += \
./Main/cr_startup_lpc176x.d \
./Main/usbhost_main.d 


# Each subdirectory must supply rules for building sources it contributes
Main/cr_startup_lpc176x.o: ../Main/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2_LPC17xx -I"D:\projects\lpcxpresso\samples\1769\lpcx\CMSISv2_LPC17xx\inc" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Fat" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Host" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Include" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Main" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\MassStorage" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Uart" -O0 -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"Main/cr_startup_lpc176x.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Main/%.o: ../Main/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2_LPC17xx -I"D:\projects\lpcxpresso\samples\1769\lpcx\CMSISv2_LPC17xx\inc" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Fat" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Host" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Include" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Main" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\MassStorage" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Uart" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


