################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MiddleWares/Third_Party/org/Source/croutine.c \
../MiddleWares/Third_Party/org/Source/event_groups.c \
../MiddleWares/Third_Party/org/Source/list.c \
../MiddleWares/Third_Party/org/Source/queue.c \
../MiddleWares/Third_Party/org/Source/stream_buffer.c \
../MiddleWares/Third_Party/org/Source/tasks.c \
../MiddleWares/Third_Party/org/Source/timers.c 

OBJS += \
./MiddleWares/Third_Party/org/Source/croutine.o \
./MiddleWares/Third_Party/org/Source/event_groups.o \
./MiddleWares/Third_Party/org/Source/list.o \
./MiddleWares/Third_Party/org/Source/queue.o \
./MiddleWares/Third_Party/org/Source/stream_buffer.o \
./MiddleWares/Third_Party/org/Source/tasks.o \
./MiddleWares/Third_Party/org/Source/timers.o 

C_DEPS += \
./MiddleWares/Third_Party/org/Source/croutine.d \
./MiddleWares/Third_Party/org/Source/event_groups.d \
./MiddleWares/Third_Party/org/Source/list.d \
./MiddleWares/Third_Party/org/Source/queue.d \
./MiddleWares/Third_Party/org/Source/stream_buffer.d \
./MiddleWares/Third_Party/org/Source/tasks.d \
./MiddleWares/Third_Party/org/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
MiddleWares/Third_Party/org/Source/croutine.o: ../MiddleWares/Third_Party/org/Source/croutine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/FreeRTOSConfig" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/include" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/MemMang" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MiddleWares/Third_Party/org/Source/croutine.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MiddleWares/Third_Party/org/Source/event_groups.o: ../MiddleWares/Third_Party/org/Source/event_groups.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/FreeRTOSConfig" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/include" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/MemMang" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MiddleWares/Third_Party/org/Source/event_groups.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MiddleWares/Third_Party/org/Source/list.o: ../MiddleWares/Third_Party/org/Source/list.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/FreeRTOSConfig" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/include" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/MemMang" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MiddleWares/Third_Party/org/Source/list.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MiddleWares/Third_Party/org/Source/queue.o: ../MiddleWares/Third_Party/org/Source/queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/FreeRTOSConfig" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/include" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/MemMang" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MiddleWares/Third_Party/org/Source/queue.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MiddleWares/Third_Party/org/Source/stream_buffer.o: ../MiddleWares/Third_Party/org/Source/stream_buffer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/FreeRTOSConfig" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/include" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/MemMang" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MiddleWares/Third_Party/org/Source/stream_buffer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MiddleWares/Third_Party/org/Source/tasks.o: ../MiddleWares/Third_Party/org/Source/tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/FreeRTOSConfig" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/include" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/MemMang" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MiddleWares/Third_Party/org/Source/tasks.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MiddleWares/Third_Party/org/Source/timers.o: ../MiddleWares/Third_Party/org/Source/timers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/FreeRTOSConfig" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/include" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/GCC/ARM_CM4F" -I"D:/FREERTOS/FREERTOS_IDE/001_FREERTOS_LED_CONTROL_WITH_BUTTON/MiddleWares/Third_Party/org/Source/portable/MemMang" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MiddleWares/Third_Party/org/Source/timers.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

