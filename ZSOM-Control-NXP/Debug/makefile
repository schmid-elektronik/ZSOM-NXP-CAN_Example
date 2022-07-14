################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/CANopen/subdir.mk
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
all: ZSOM-Control-NXP.axf

# Tool invocations
ZSOM-Control-NXP.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\LA\Documents\CanExample\nxp_lpcxpresso_11c24_board_lib\Debug" -L"C:\Users\LA\Documents\CanExample\lpc_chip_11cxx_lib\Debug" -Xlinker -Map="ZSOM-Control-NXP.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "ZSOM-Control-NXP_Debug.ld" -o "ZSOM-Control-NXP.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) ZSOM-Control-NXP.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "ZSOM-Control-NXP.axf"; # arm-none-eabi-objcopy -v -O binary "ZSOM-Control-NXP.axf" "ZSOM-Control-NXP.bin" ; # checksum -p LPC11C24_301 -d "ZSOM-Control-NXP.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
