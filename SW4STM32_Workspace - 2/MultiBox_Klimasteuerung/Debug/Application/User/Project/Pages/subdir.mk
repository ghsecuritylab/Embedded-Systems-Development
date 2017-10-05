################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Project/Pages/AnzeigeDLG.c \
../Application/User/Project/Pages/Dialog_NewTimerEvent.c \
../Application/User/Project/Pages/Project_Page_Main_1.c \
../Application/User/Project/Pages/Project_Page_Main_2.c \
../Application/User/Project/Pages/Project_Page_Main_3.c 

OBJS += \
./Application/User/Project/Pages/AnzeigeDLG.o \
./Application/User/Project/Pages/Dialog_NewTimerEvent.o \
./Application/User/Project/Pages/Project_Page_Main_1.o \
./Application/User/Project/Pages/Project_Page_Main_2.o \
./Application/User/Project/Pages/Project_Page_Main_3.o 

C_DEPS += \
./Application/User/Project/Pages/AnzeigeDLG.d \
./Application/User/Project/Pages/Dialog_NewTimerEvent.d \
./Application/User/Project/Pages/Project_Page_Main_1.d \
./Application/User/Project/Pages/Project_Page_Main_2.d \
./Application/User/Project/Pages/Project_Page_Main_3.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Project/Pages/%.o: ../Application/User/Project/Pages/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCOVERY -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Driver/AdapterBoard" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Driver/Click boards" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Driver/Communication" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Driver/SD-Card" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Dialogs" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Header" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Icons" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Layout" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Loading Screen" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Menu" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/GUI-Interface" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Main/STemWin-Conf" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Main" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Memory/Data" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Memory/Lookup" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Memory/Parameter" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Memory/RingMemory" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Project/Pages" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Project" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Drivers/BSP/Components/ft5336" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Memory" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Driver" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Driver/1Wire-Devices" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Firmware" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Firmware/Functions" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Firmware/Pages" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 2/MultiBox_Klimasteuerung/Application/User/Driver/RTC" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/CMSIS/Include" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/BSP/STM32746G-Discovery" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/BSP/Components/Common" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/BSP/Components" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Middlewares/ST/STemWin/inc" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Utilities" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Utilities/Fonts" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Middlewares/Third_Party/FatFs/src" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Middlewares/Third_Party/FatFs/src/drivers"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


