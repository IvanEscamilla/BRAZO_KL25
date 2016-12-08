################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/LEDS.c" \
"../Sources/PWM.c" \
"../Sources/UART0.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/LEDS.c \
../Sources/PWM.c \
../Sources/UART0.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/LEDS.o \
./Sources/PWM.o \
./Sources/UART0.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/LEDS.d \
./Sources/PWM.d \
./Sources/UART0.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/LEDS.o" \
"./Sources/PWM.o" \
"./Sources/UART0.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/LEDS.d" \
"./Sources/PWM.d" \
"./Sources/UART0.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/LEDS.o \
./Sources/PWM.o \
./Sources/UART0.o \
./Sources/main.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/LEDS.o: ../Sources/LEDS.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LEDS.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LEDS.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/PWM.o: ../Sources/PWM.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/PWM.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/PWM.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/UART0.o: ../Sources/UART0.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/UART0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/UART0.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


