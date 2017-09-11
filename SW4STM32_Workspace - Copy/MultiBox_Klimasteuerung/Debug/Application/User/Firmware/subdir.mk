################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Firmware/Firmware_Data_CONFIG.c \
../Application/User/Firmware/Firmware_Lookup_CONFIG.c \
../Application/User/Firmware/Firmware_MenuView_CONFIG.c \
../Application/User/Firmware/Firmware_Pages_CONFIG.c \
../Application/User/Firmware/Firmware_Parameter_CONFIG.c \
../Application/User/Firmware/Firmware_ProcessControl.c \
../Application/User/Firmware/Firmware_RingMemory_CONFIG.c 

OBJS += \
./Application/User/Firmware/Firmware_Data_CONFIG.o \
./Application/User/Firmware/Firmware_Lookup_CONFIG.o \
./Application/User/Firmware/Firmware_MenuView_CONFIG.o \
./Application/User/Firmware/Firmware_Pages_CONFIG.o \
./Application/User/Firmware/Firmware_Parameter_CONFIG.o \
./Application/User/Firmware/Firmware_ProcessControl.o \
./Application/User/Firmware/Firmware_RingMemory_CONFIG.o 

C_DEPS += \
./Application/User/Firmware/Firmware_Data_CONFIG.d \
./Application/User/Firmware/Firmware_Lookup_CONFIG.d \
./Application/User/Firmware/Firmware_MenuView_CONFIG.d \
./Application/User/Firmware/Firmware_Pages_CONFIG.d \
./Application/User/Firmware/Firmware_Parameter_CONFIG.d \
./Application/User/Firmware/Firmware_ProcessControl.d \
./Application/User/Firmware/Firmware_RingMemory_CONFIG.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Firmware/%.o: ../Application/User/Firmware/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCOVERY -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Driver/AdapterBoard" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Driver/Click boards" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Driver/Communication" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Driver/SD-Card" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Dialogs" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Header" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Icons" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Layout" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Loading Screen" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Menu" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/GUI-Interface" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Main/STemWin-Conf" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Main" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Memory/Data" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Memory/Lookup" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Memory/Parameter" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Memory/RingMemory" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Project/Pages" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Project" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Drivers/BSP/Components/ft5336" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Memory" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Driver" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Driver/1Wire-Devices" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Firmware" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Firmware/Functions" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Firmware/Pages" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - Copy/MultiBox_Klimasteuerung/Application/User/Driver/RTC" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/CMSIS/Include" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/BSP/STM32746G-Discovery" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/BSP/Components/Common" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/BSP/Components" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Middlewares/ST/STemWin/inc" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Utilities" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Utilities/Fonts" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Middlewares/Third_Party/FatFs/src" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Middlewares/Third_Party/FatFs/src/drivers"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


