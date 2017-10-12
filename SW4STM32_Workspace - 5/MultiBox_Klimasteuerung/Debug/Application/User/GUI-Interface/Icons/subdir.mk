################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/GUI-Interface/Icons/Back.c \
../Application/User/GUI-Interface/Icons/Bild3.c \
../Application/User/GUI-Interface/Icons/Cancel.c \
../Application/User/GUI-Interface/Icons/DEFAULT.c \
../Application/User/GUI-Interface/Icons/DataType_D.c \
../Application/User/GUI-Interface/Icons/DataType_IO.c \
../Application/User/GUI-Interface/Icons/DataType_Int.c \
../Application/User/GUI-Interface/Icons/DataType_P.c \
../Application/User/GUI-Interface/Icons/Down.c \
../Application/User/GUI-Interface/Icons/Fliesskomma.c \
../Application/User/GUI-Interface/Icons/Hardware.c \
../Application/User/GUI-Interface/Icons/IAV.c \
../Application/User/GUI-Interface/Icons/Main.c \
../Application/User/GUI-Interface/Icons/Menu.c \
../Application/User/GUI-Interface/Icons/Ok.c \
../Application/User/GUI-Interface/Icons/Stop.c \
../Application/User/GUI-Interface/Icons/System.c \
../Application/User/GUI-Interface/Icons/Up.c \
../Application/User/GUI-Interface/Icons/check.c \
../Application/User/GUI-Interface/Icons/clear.c \
../Application/User/GUI-Interface/Icons/home.c \
../Application/User/GUI-Interface/Icons/numeric_keypad.c \
../Application/User/GUI-Interface/Icons/sort_up_down.c \
../Application/User/GUI-Interface/Icons/switch_off.c \
../Application/User/GUI-Interface/Icons/switch_on.c \
../Application/User/GUI-Interface/Icons/window_information.c 

OBJS += \
./Application/User/GUI-Interface/Icons/Back.o \
./Application/User/GUI-Interface/Icons/Bild3.o \
./Application/User/GUI-Interface/Icons/Cancel.o \
./Application/User/GUI-Interface/Icons/DEFAULT.o \
./Application/User/GUI-Interface/Icons/DataType_D.o \
./Application/User/GUI-Interface/Icons/DataType_IO.o \
./Application/User/GUI-Interface/Icons/DataType_Int.o \
./Application/User/GUI-Interface/Icons/DataType_P.o \
./Application/User/GUI-Interface/Icons/Down.o \
./Application/User/GUI-Interface/Icons/Fliesskomma.o \
./Application/User/GUI-Interface/Icons/Hardware.o \
./Application/User/GUI-Interface/Icons/IAV.o \
./Application/User/GUI-Interface/Icons/Main.o \
./Application/User/GUI-Interface/Icons/Menu.o \
./Application/User/GUI-Interface/Icons/Ok.o \
./Application/User/GUI-Interface/Icons/Stop.o \
./Application/User/GUI-Interface/Icons/System.o \
./Application/User/GUI-Interface/Icons/Up.o \
./Application/User/GUI-Interface/Icons/check.o \
./Application/User/GUI-Interface/Icons/clear.o \
./Application/User/GUI-Interface/Icons/home.o \
./Application/User/GUI-Interface/Icons/numeric_keypad.o \
./Application/User/GUI-Interface/Icons/sort_up_down.o \
./Application/User/GUI-Interface/Icons/switch_off.o \
./Application/User/GUI-Interface/Icons/switch_on.o \
./Application/User/GUI-Interface/Icons/window_information.o 

C_DEPS += \
./Application/User/GUI-Interface/Icons/Back.d \
./Application/User/GUI-Interface/Icons/Bild3.d \
./Application/User/GUI-Interface/Icons/Cancel.d \
./Application/User/GUI-Interface/Icons/DEFAULT.d \
./Application/User/GUI-Interface/Icons/DataType_D.d \
./Application/User/GUI-Interface/Icons/DataType_IO.d \
./Application/User/GUI-Interface/Icons/DataType_Int.d \
./Application/User/GUI-Interface/Icons/DataType_P.d \
./Application/User/GUI-Interface/Icons/Down.d \
./Application/User/GUI-Interface/Icons/Fliesskomma.d \
./Application/User/GUI-Interface/Icons/Hardware.d \
./Application/User/GUI-Interface/Icons/IAV.d \
./Application/User/GUI-Interface/Icons/Main.d \
./Application/User/GUI-Interface/Icons/Menu.d \
./Application/User/GUI-Interface/Icons/Ok.d \
./Application/User/GUI-Interface/Icons/Stop.d \
./Application/User/GUI-Interface/Icons/System.d \
./Application/User/GUI-Interface/Icons/Up.d \
./Application/User/GUI-Interface/Icons/check.d \
./Application/User/GUI-Interface/Icons/clear.d \
./Application/User/GUI-Interface/Icons/home.d \
./Application/User/GUI-Interface/Icons/numeric_keypad.d \
./Application/User/GUI-Interface/Icons/sort_up_down.d \
./Application/User/GUI-Interface/Icons/switch_off.d \
./Application/User/GUI-Interface/Icons/switch_on.d \
./Application/User/GUI-Interface/Icons/window_information.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/GUI-Interface/Icons/%.o: ../Application/User/GUI-Interface/Icons/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCOVERY -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Driver/AdapterBoard" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Driver/Click boards" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Driver/Communication" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Driver/SD-Card" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Dialogs" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Header" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Icons" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Layout" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Loading Screen" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/GUI-Interface/Menu" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/GUI-Interface" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Main/STemWin-Conf" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Main" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Memory/Data" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Memory/Lookup" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Memory/Parameter" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Memory/RingMemory" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Project/Pages" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Project" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Drivers/BSP/Components/ft5336" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Memory" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Driver" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Driver/1Wire-Devices" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Firmware" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Firmware/Functions" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Firmware/Pages" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/SW4STM32_Workspace - 5/MultiBox_Klimasteuerung/Application/User/Driver/RTC" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/CMSIS/Include" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/BSP/STM32746G-Discovery" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/BSP/Components/Common" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Drivers/BSP/Components" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Middlewares/ST/STemWin/inc" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Utilities" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Utilities/Fonts" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Middlewares/Third_Party/FatFs/src" -I"C:/Users/lzhang/Workspace/MultiBox_KlimaKSB/STM32Cube_FW_F7_AKT/Middlewares/Third_Party/FatFs/src/drivers"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


