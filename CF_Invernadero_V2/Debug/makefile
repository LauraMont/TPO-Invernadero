################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/systick/subdir.mk
-include src/pll/subdir.mk
-include src/gpio/subdir.mk
-include src/Temporizadores/subdir.mk
-include src/RTC/subdir.mk
-include src/Inicializacion/subdir.mk
-include src/I2C/subdir.mk
-include src/Display/subdir.mk
-include src/Datos/subdir.mk
-include src/BMP280/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: CF_Invernadero_V2.axf

# Tool invocations
CF_Invernadero_V2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="CF_Invernadero_V2.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "CF_Invernadero_V2_Debug.ld" -o "CF_Invernadero_V2.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) CF_Invernadero_V2.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "CF_Invernadero_V2.axf"; # arm-none-eabi-objcopy -v -O binary "CF_Invernadero_V2.axf" "CF_Invernadero_V2.bin" ; # checksum -p LPC1769 -d "CF_Invernadero_V2.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
