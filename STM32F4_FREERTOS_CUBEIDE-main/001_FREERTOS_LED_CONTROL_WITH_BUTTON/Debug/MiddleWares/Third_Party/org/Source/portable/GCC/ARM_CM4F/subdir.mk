################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F/port.o: ../MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F/port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/FreeRTOSConfig" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/include" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/MemMang" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F/port.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

