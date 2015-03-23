################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../localSignalParser.cpp \
../localSignals.cpp \
../main.cpp \
../parserFunctions.cpp 

OBJS += \
./localSignalParser.o \
./localSignals.o \
./main.o \
./parserFunctions.o 

CPP_DEPS += \
./localSignalParser.d \
./localSignals.d \
./main.d \
./parserFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I.././ -I/usr/include/boost -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


