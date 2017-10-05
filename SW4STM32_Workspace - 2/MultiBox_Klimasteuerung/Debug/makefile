################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FatFs/src/drivers/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include Middlewares/STemWin/Config/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/STM32746G_DISCOVERY/subdir.mk
-include Drivers/BSP/Components/ft5336/subdir.mk
-include Application/User/Project/Pages/subdir.mk
-include Application/User/Project/subdir.mk
-include Application/User/Memory/RingMemory/subdir.mk
-include Application/User/Memory/Parameter/subdir.mk
-include Application/User/Memory/Lookup/subdir.mk
-include Application/User/Main/STemWin-Conf/subdir.mk
-include Application/User/Main/subdir.mk
-include Application/User/GUI-Interface/Menu/subdir.mk
-include Application/User/GUI-Interface/Loading\ Screen/subdir.mk
-include Application/User/GUI-Interface/Layout/subdir.mk
-include Application/User/GUI-Interface/Icons/subdir.mk
-include Application/User/GUI-Interface/Header/subdir.mk
-include Application/User/GUI-Interface/Dialogs/subdir.mk
-include Application/User/GUI-Interface/subdir.mk
-include Application/User/Firmware/Pages/subdir.mk
-include Application/User/Firmware/Functions/subdir.mk
-include Application/User/Firmware/subdir.mk
-include Application/User/Driver/SD-Card/subdir.mk
-include Application/User/Driver/RTC/subdir.mk
-include Application/User/Driver/Communication/subdir.mk
-include Application/User/Driver/Click\ boards/subdir.mk
-include Application/User/Driver/AdapterBoard/subdir.mk
-include Application/User/Driver/1Wire-Devices/subdir.mk
-include Application/SW4STM32/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: STM32746G_DISCOVERY.elf

# Tool invocations
STM32746G_DISCOVERY.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -L"C:\Users\lzhang\Workspace\MultiBox_KlimaKSB\STM32Cube_FW_F7_AKT\Middlewares\ST\STemWin\Lib"  -specs=nosys.specs -u _printf_float -u _scanf_float -T"../STM32F746NGHx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "STM32746G_DISCOVERY.elf" @"objects.list" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "STM32746G_DISCOVERY.elf" "STM32746G_DISCOVERY.bin"
	arm-none-eabi-size "STM32746G_DISCOVERY.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
