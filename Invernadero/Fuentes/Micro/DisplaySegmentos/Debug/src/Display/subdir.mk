################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Display/DR_Display.c \
../src/Display/PR_Display.c 

OBJS += \
./src/Display/DR_Display.o \
./src/Display/PR_Display.o 

C_DEPS += \
./src/Display/DR_Display.d \
./src/Display/PR_Display.d 


# Each subdirectory must supply rules for building sources it contributes
src/Display/%.o: ../src/Display/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/DisplaySegmentos/src/Display" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/DisplaySegmentos/src/gpio" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/DisplaySegmentos/src/systick" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


