################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/canHandler.c \
../src/cr_startup_lpc11xx.c \
../src/crp.c \
../src/main.c \
../src/sysinit.c 

OBJS += \
./src/canHandler.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/main.o \
./src/sysinit.o 

C_DEPS += \
./src/canHandler.d \
./src/cr_startup_lpc11xx.d \
./src/crp.d \
./src/main.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11XX__ -D__REDLIB__ -I"C:\Users\LA\Documents\CanExample\nxp_lpcxpresso_11c24_board_lib\inc" -I"C:\Users\LA\Documents\CanExample\lpc_chip_11cxx_lib\inc" -I"C:\Users\LA\Documents\CanExample\ZSOM-Control-NXP\src\CANopen" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


