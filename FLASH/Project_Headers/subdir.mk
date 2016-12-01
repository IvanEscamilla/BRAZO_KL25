################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Headers/GPIO.c" \

C_SRCS += \
../Project_Headers/GPIO.c \

OBJS += \
./Project_Headers/GPIO.o \

C_DEPS += \
./Project_Headers/GPIO.d \

OBJS_QUOTED += \
"./Project_Headers/GPIO.o" \

C_DEPS_QUOTED += \
"./Project_Headers/GPIO.d" \

OBJS_OS_FORMAT += \
./Project_Headers/GPIO.o \


# Each subdirectory must supply rules for building sources it contributes
Project_Headers/GPIO.o: ../Project_Headers/GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Headers/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Headers/GPIO.o"
	@echo 'Finished building: $<'
	@echo ' '


