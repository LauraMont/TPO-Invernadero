################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adcuser.c \
../src/cr_startup_lpc176x.c \
../src/usbcore.c \
../src/usbdesc.c \
../src/usbdmain.c \
../src/usbhw.c \
../src/usbuser.c 

OBJS += \
./src/adcuser.o \
./src/cr_startup_lpc176x.o \
./src/usbcore.o \
./src/usbdesc.o \
./src/usbdmain.o \
./src/usbhw.o \
./src/usbuser.o 

C_DEPS += \
./src/adcuser.d \
./src/cr_startup_lpc176x.d \
./src/usbcore.d \
./src/usbdesc.d \
./src/usbdmain.d \
./src/usbhw.d \
./src/usbuser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2_LPC17xx -I"D:\projects\lpcxpresso\samples\1769\lpcx\CMSISv2_LPC17xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc176x.o: ../src/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2_LPC17xx -I"D:\projects\lpcxpresso\samples\1769\lpcx\CMSISv2_LPC17xx\inc" -O0 -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc176x.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


