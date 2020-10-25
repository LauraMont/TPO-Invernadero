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
-include src/Display/subdir.mk
-include src/ADC/subdir.mk
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
all: DisplaySegmentos.axf

# Tool invocations
DisplaySegmentos.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="DisplaySegmentos.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "DisplaySegmentos_Debug.ld" -o "DisplaySegmentos.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) DisplaySegmentos.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "DisplaySegmentos.axf"; # arm-none-eabi-objcopy -v -O binary "DisplaySegmentos.axf" "DisplaySegmentos.bin" ; # checksum -p LPC1769 -d "DisplaySegmentos.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
