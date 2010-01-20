################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../message.cpp \
../plugin-connector.cpp \
../simpleserver.cpp \
../xmppnegotiation.cpp 

OBJS += \
./message.o \
./plugin-connector.o \
./simpleserver.o \
./xmppnegotiation.o 

CPP_DEPS += \
./message.d \
./plugin-connector.d \
./simpleserver.d \
./xmppnegotiation.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/heverton/workspace/streamadapt/streamadapt/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


