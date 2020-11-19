################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DR_GPIO.c \
../src/DR_PINSEL.c \
../src/DR_PLL.c \
../src/DR_SYSTICK.c \
../src/DR_UART0.c \
../src/DR_timer.c \
../src/Indicador_nivel.c \
../src/PR_UART0.c \
../src/PR_timer.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/rx_trama.c 

OBJS += \
./src/DR_GPIO.o \
./src/DR_PINSEL.o \
./src/DR_PLL.o \
./src/DR_SYSTICK.o \
./src/DR_UART0.o \
./src/DR_timer.o \
./src/Indicador_nivel.o \
./src/PR_UART0.o \
./src/PR_timer.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/rx_trama.o 

C_DEPS += \
./src/DR_GPIO.d \
./src/DR_PINSEL.d \
./src/DR_PLL.d \
./src/DR_SYSTICK.d \
./src/DR_UART0.d \
./src/DR_timer.d \
./src/Indicador_nivel.d \
./src/PR_UART0.d \
./src/PR_timer.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/rx_trama.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/javier/UTN/Info2/Clases/Indicador_nivel/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


