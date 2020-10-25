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
-include src/Inicializacion/subdir.mk
-include src/I2C/subdir.mk
-include src/Display/subdir.mk
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
all: TPO.axf

# Tool invocations
TPO.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="TPO.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "TPO_Debug.ld" -o "TPO.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) TPO.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "TPO.axf"; # arm-none-eabi-objcopy -v -O binary "TPO.axf" "TPO.bin" ; # checksum -p LPC1769 -d "TPO.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
