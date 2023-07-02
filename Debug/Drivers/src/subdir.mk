################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/src/Srec_reader.c \
../Drivers/src/core_cm3.c \
../Drivers/src/gpio.c \
../Drivers/src/misc.c \
../Drivers/src/queue.c \
../Drivers/src/stm32f10x_flash.c \
../Drivers/src/stm32f10x_rcc.c \
../Drivers/src/stm32f10x_usart.c \
../Drivers/src/system_stm32f10x.c 

OBJS += \
./Drivers/src/Srec_reader.o \
./Drivers/src/core_cm3.o \
./Drivers/src/gpio.o \
./Drivers/src/misc.o \
./Drivers/src/queue.o \
./Drivers/src/stm32f10x_flash.o \
./Drivers/src/stm32f10x_rcc.o \
./Drivers/src/stm32f10x_usart.o \
./Drivers/src/system_stm32f10x.o 

C_DEPS += \
./Drivers/src/Srec_reader.d \
./Drivers/src/core_cm3.d \
./Drivers/src/gpio.d \
./Drivers/src/misc.d \
./Drivers/src/queue.d \
./Drivers/src/stm32f10x_flash.d \
./Drivers/src/stm32f10x_rcc.d \
./Drivers/src/stm32f10x_usart.d \
./Drivers/src/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/src/%.o Drivers/src/%.su: ../Drivers/src/%.c Drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I../Inc -I"D:/stm32_cube sofware/embeded_stm32/test_8/Drivers/inc" -I"D:/stm32_cube sofware/embeded_stm32/test_8/Interrupt" -I"D:/stm32_cube sofware/embeded_stm32/test_8/App" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-src

clean-Drivers-2f-src:
	-$(RM) ./Drivers/src/Srec_reader.d ./Drivers/src/Srec_reader.o ./Drivers/src/Srec_reader.su ./Drivers/src/core_cm3.d ./Drivers/src/core_cm3.o ./Drivers/src/core_cm3.su ./Drivers/src/gpio.d ./Drivers/src/gpio.o ./Drivers/src/gpio.su ./Drivers/src/misc.d ./Drivers/src/misc.o ./Drivers/src/misc.su ./Drivers/src/queue.d ./Drivers/src/queue.o ./Drivers/src/queue.su ./Drivers/src/stm32f10x_flash.d ./Drivers/src/stm32f10x_flash.o ./Drivers/src/stm32f10x_flash.su ./Drivers/src/stm32f10x_rcc.d ./Drivers/src/stm32f10x_rcc.o ./Drivers/src/stm32f10x_rcc.su ./Drivers/src/stm32f10x_usart.d ./Drivers/src/stm32f10x_usart.o ./Drivers/src/stm32f10x_usart.su ./Drivers/src/system_stm32f10x.d ./Drivers/src/system_stm32f10x.o ./Drivers/src/system_stm32f10x.su

.PHONY: clean-Drivers-2f-src

