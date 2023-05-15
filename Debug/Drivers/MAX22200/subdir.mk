################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MAX22200/MAX22200_driver.c 

C_DEPS += \
./Drivers/MAX22200/MAX22200_driver.d 

OBJS += \
./Drivers/MAX22200/MAX22200_driver.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MAX22200/%.o Drivers/MAX22200/%.su Drivers/MAX22200/%.cyclo: ../Drivers/MAX22200/%.c Drivers/MAX22200/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/nir/Desktop/Test_MAX22200/App" -I"/home/nir/Desktop/Test_MAX22200/Drivers/MAX22200" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-MAX22200

clean-Drivers-2f-MAX22200:
	-$(RM) ./Drivers/MAX22200/MAX22200_driver.cyclo ./Drivers/MAX22200/MAX22200_driver.d ./Drivers/MAX22200/MAX22200_driver.o ./Drivers/MAX22200/MAX22200_driver.su

.PHONY: clean-Drivers-2f-MAX22200

