################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Fat/usbhost_fat.c 

OBJS += \
./Fat/usbhost_fat.o 

C_DEPS += \
./Fat/usbhost_fat.d 


# Each subdirectory must supply rules for building sources it contributes
Fat/%.o: ../Fat/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2_LPC17xx -I"D:\projects\lpcxpresso\samples\1769\lpcx\CMSISv2_LPC17xx\inc" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Fat" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Host" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Include" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Main" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\MassStorage" -I"D:\projects\lpcxpresso\samples\1769\lpcx\USBHostLite\Uart" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


