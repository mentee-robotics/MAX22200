################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../App/Motor/Motor.cpp 

OBJS += \
./App/Motor/Motor.o 

CPP_DEPS += \
./App/Motor/Motor.d 


# Each subdirectory must supply rules for building sources it contributes
App/Motor/%.o App/Motor/%.su App/Motor/%.cyclo: ../App/Motor/%.cpp App/Motor/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/nir/Desktop/Test_MAX22200/App" -I"/home/nir/Desktop/Test_MAX22200/App/MAX22200" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Motor

clean-App-2f-Motor:
	-$(RM) ./App/Motor/Motor.cyclo ./App/Motor/Motor.d ./App/Motor/Motor.o ./App/Motor/Motor.su

.PHONY: clean-App-2f-Motor

