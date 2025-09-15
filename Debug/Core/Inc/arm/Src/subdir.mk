################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/arm/Src/arm.cpp 

OBJS += \
./Core/Inc/arm/Src/arm.o 

CPP_DEPS += \
./Core/Inc/arm/Src/arm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/arm/Src/%.o Core/Inc/arm/Src/%.su Core/Inc/arm/Src/%.cyclo: ../Core/Inc/arm/Src/%.cpp Core/Inc/arm/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-arm-2f-Src

clean-Core-2f-Inc-2f-arm-2f-Src:
	-$(RM) ./Core/Inc/arm/Src/arm.cyclo ./Core/Inc/arm/Src/arm.d ./Core/Inc/arm/Src/arm.o ./Core/Inc/arm/Src/arm.su

.PHONY: clean-Core-2f-Inc-2f-arm-2f-Src

