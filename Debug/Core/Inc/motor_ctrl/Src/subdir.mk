################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/motor_ctrl/Src/motor_ctrl.cpp \
../Core/Inc/motor_ctrl/Src/motor_monitor.cpp 

OBJS += \
./Core/Inc/motor_ctrl/Src/motor_ctrl.o \
./Core/Inc/motor_ctrl/Src/motor_monitor.o 

CPP_DEPS += \
./Core/Inc/motor_ctrl/Src/motor_ctrl.d \
./Core/Inc/motor_ctrl/Src/motor_monitor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/motor_ctrl/Src/%.o Core/Inc/motor_ctrl/Src/%.su Core/Inc/motor_ctrl/Src/%.cyclo: ../Core/Inc/motor_ctrl/Src/%.cpp Core/Inc/motor_ctrl/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-motor_ctrl-2f-Src

clean-Core-2f-Inc-2f-motor_ctrl-2f-Src:
	-$(RM) ./Core/Inc/motor_ctrl/Src/motor_ctrl.cyclo ./Core/Inc/motor_ctrl/Src/motor_ctrl.d ./Core/Inc/motor_ctrl/Src/motor_ctrl.o ./Core/Inc/motor_ctrl/Src/motor_ctrl.su ./Core/Inc/motor_ctrl/Src/motor_monitor.cyclo ./Core/Inc/motor_ctrl/Src/motor_monitor.d ./Core/Inc/motor_ctrl/Src/motor_monitor.o ./Core/Inc/motor_ctrl/Src/motor_monitor.su

.PHONY: clean-Core-2f-Inc-2f-motor_ctrl-2f-Src

