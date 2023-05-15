################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../App/MAX22200/MAX22200_driver.cpp 

OBJS += \
./App/MAX22200/MAX22200_driver.o 

CPP_DEPS += \
./App/MAX22200/MAX22200_driver.d 


# Each subdirectory must supply rules for building sources it contributes
App/MAX22200/%.o App/MAX22200/%.su App/MAX22200/%.cyclo: ../App/MAX22200/%.cpp App/MAX22200/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/nir/Desktop/Test_MAX22200/App" -I"/home/nir/Desktop/Test_MAX22200/App/MAX22200" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-MAX22200

clean-App-2f-MAX22200:
	-$(RM) ./App/MAX22200/MAX22200_driver.cyclo ./App/MAX22200/MAX22200_driver.d ./App/MAX22200/MAX22200_driver.o ./App/MAX22200/MAX22200_driver.su

.PHONY: clean-App-2f-MAX22200

