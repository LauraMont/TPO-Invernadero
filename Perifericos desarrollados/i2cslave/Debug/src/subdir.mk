################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc176x.c \
../src/i2cslave0.c \
../src/i2cslave1.c \
../src/i2cslave2.c \
../src/i2cslvtst.c 

OBJS += \
./src/cr_startup_lpc176x.o \
./src/i2cslave0.o \
./src/i2cslave1.o \
./src/i2cslave2.o \
./src/i2cslvtst.o 

C_DEPS += \
./src/cr_startup_lpc176x.d \
./src/i2cslave0.d \
./src/i2cslave1.d \
./src/i2cslave2.d \
./src/i2cslvtst.d 


# Each subdirectory must supply rules for building sources it contributes
src/cr_startup_lpc176x.o: ../src/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2_LPC17xx -I"D:\projects\lpcxpresso\samples\1769\lpcx\CMSISv2_LPC17xx\inc" -O0 -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc176x.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2_LPC17xx -I"D:\projects\lpcxpresso\samples\1769\lpcx\CMSISv2_LPC17xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


