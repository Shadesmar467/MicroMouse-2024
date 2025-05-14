################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../floodfill/programs/floodFill.c \
../floodfill/programs/main.c \
../floodfill/programs/mazeFunctions.c \
../floodfill/programs/mouseFunctions.c \
../floodfill/programs/utilityFunctions.c 

C_DEPS += \
./floodfill/programs/floodFill.d \
./floodfill/programs/main.d \
./floodfill/programs/mazeFunctions.d \
./floodfill/programs/mouseFunctions.d \
./floodfill/programs/utilityFunctions.d 

OBJS += \
./floodfill/programs/floodFill.o \
./floodfill/programs/main.o \
./floodfill/programs/mazeFunctions.o \
./floodfill/programs/mouseFunctions.o \
./floodfill/programs/utilityFunctions.o 


# Each subdirectory must supply rules for building sources it contributes
floodfill/programs/%.o floodfill/programs/%.su floodfill/programs/%.cyclo: ../floodfill/programs/%.c floodfill/programs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../floodfill/headers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-floodfill-2f-programs

clean-floodfill-2f-programs:
	-$(RM) ./floodfill/programs/floodFill.cyclo ./floodfill/programs/floodFill.d ./floodfill/programs/floodFill.o ./floodfill/programs/floodFill.su ./floodfill/programs/main.cyclo ./floodfill/programs/main.d ./floodfill/programs/main.o ./floodfill/programs/main.su ./floodfill/programs/mazeFunctions.cyclo ./floodfill/programs/mazeFunctions.d ./floodfill/programs/mazeFunctions.o ./floodfill/programs/mazeFunctions.su ./floodfill/programs/mouseFunctions.cyclo ./floodfill/programs/mouseFunctions.d ./floodfill/programs/mouseFunctions.o ./floodfill/programs/mouseFunctions.su ./floodfill/programs/utilityFunctions.cyclo ./floodfill/programs/utilityFunctions.d ./floodfill/programs/utilityFunctions.o ./floodfill/programs/utilityFunctions.su

.PHONY: clean-floodfill-2f-programs

