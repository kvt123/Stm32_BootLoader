################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Interrupt/stm32f10x_it.c 

OBJS += \
./Interrupt/stm32f10x_it.o 

C_DEPS += \
./Interrupt/stm32f10x_it.d 


# Each subdirectory must supply rules for building sources it contributes
Interrupt/%.o Interrupt/%.su: ../Interrupt/%.c Interrupt/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I../Inc -I"D:/stm32_cube sofware/embeded_stm32/test_8/Drivers/inc" -I"D:/stm32_cube sofware/embeded_stm32/test_8/Interrupt" -I"D:/stm32_cube sofware/embeded_stm32/test_8/App" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Interrupt

clean-Interrupt:
	-$(RM) ./Interrupt/stm32f10x_it.d ./Interrupt/stm32f10x_it.o ./Interrupt/stm32f10x_it.su

.PHONY: clean-Interrupt

