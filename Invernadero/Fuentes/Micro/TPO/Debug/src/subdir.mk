################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/I2C" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/Inicializacion" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/pll" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/systick" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/Display" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/Temporizadores" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/LCD" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/GPIO" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/Aplicacion" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/Teclado" -I"/home/nico/Nico/UTN/Info2/TPO-Invernadero/Invernadero/Fuentes/Micro/TPO/src/BME280" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


