################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Uart/subdir.mk
-include MassStorage/subdir.mk
-include Main/subdir.mk
-include Host/subdir.mk
-include Fat/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: USBHostLite.axf

# Tool invocations
USBHostLite.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"D:\projects\lpcxpresso\samples\1769\lpcx\CMSISv2_LPC17xx\Debug" -Xlinker -Map=USBHostLite.map -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "USBHostLite_Debug.ld" -o"USBHostLite.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) USBHostLite.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size USBHostLite.axf; # arm-none-eabi-objcopy -O binary USBHostLite.axf USBHostLite.bin ; checksum -p LPC1769 -d USBHostLite.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
