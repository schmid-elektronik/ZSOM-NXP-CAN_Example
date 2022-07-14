################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CANopen/CanNodeDef.c \
../src/CANopen/canopen_driver.c 

OBJS += \
./src/CANopen/CanNodeDef.o \
./src/CANopen/canopen_driver.o 

C_DEPS += \
./src/CANopen/CanNodeDef.d \
./src/CANopen/canopen_driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/CANopen/%.o: ../src/CANopen/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11XX__ -D__REDLIB__ -I"C:\Users\LA\Documents\CanExample\nxp_lpcxpresso_11c24_board_lib\inc" -I"C:\Users\LA\Documents\CanExample\ZSOM-Control-NXP\src\CANopen" -I"C:\Users\LA\Documents\CanExample\lpc_chip_11cxx_lib\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


