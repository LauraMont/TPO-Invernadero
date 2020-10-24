################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CF_Invernadero.c \
../src/DR_PLL.c \
../src/DR_SYSTICK.c \
../src/Datos.c \
../src/Sys_Iluminacion.c \
../src/Sys_Riego.c \
../src/Sys_Ventilacion.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c 

OBJS += \
./src/CF_Invernadero.o \
./src/DR_PLL.o \
./src/DR_SYSTICK.o \
./src/Datos.o \
./src/Sys_Iluminacion.o \
./src/Sys_Riego.o \
./src/Sys_Ventilacion.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o 

C_DEPS += \
./src/CF_Invernadero.d \
./src/DR_PLL.d \
./src/DR_SYSTICK.d \
./src/Datos.d \
./src/Sys_Iluminacion.d \
./src/Sys_Riego.d \
./src/Sys_Ventilacion.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


