################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

BUILD_ARTIFACT_NAME := 002_LED_CONTROL_FREERTOS_INTERNAL
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
002_LED_CONTROL_FREERTOS_INTERNAL.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
002_LED_CONTROL_FREERTOS_INTERNAL.list \

OBJCOPY_BIN += \
002_LED_CONTROL_FREERTOS_INTERNAL.bin \


# All Target
all: main-build

# Main-build Target
main-build: 002_LED_CONTROL_FREERTOS_INTERNAL.elf secondary-outputs

# Tool invocations
002_LED_CONTROL_FREERTOS_INTERNAL.elf: $(OBJS) $(USER_OBJS) D:\FREERTOS\FREERTOS_IDE\002_LED_CONTROL_FREERTOS_INTERNAL\STM32F407VGTX_FLASH.ld
	arm-none-eabi-gcc -o "002_LED_CONTROL_FREERTOS_INTERNAL.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\FREERTOS\FREERTOS_IDE\002_LED_CONTROL_FREERTOS_INTERNAL\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="002_LED_CONTROL_FREERTOS_INTERNAL.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

002_LED_CONTROL_FREERTOS_INTERNAL.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "002_LED_CONTROL_FREERTOS_INTERNAL.list"
	@echo 'Finished building: $@'
	@echo ' '

002_LED_CONTROL_FREERTOS_INTERNAL.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "002_LED_CONTROL_FREERTOS_INTERNAL.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
