################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../adaptationmanager.cpp \
../consoleappender.cpp \
../event.cpp \
../eventtype.cpp \
../facade.cpp \
../gsck.cpp \
../infrafactory.cpp \
../logger.cpp \
../loggingappender.cpp \
../main.cpp \
../pluginbase.cpp \
../pluginsfactory.cpp \
../policy.cpp \
../policyengine.cpp \
../session.cpp \
../streamsession.cpp \
../trpsession.cpp 

OBJS += \
./adaptationmanager.o \
./consoleappender.o \
./event.o \
./eventtype.o \
./facade.o \
./gsck.o \
./infrafactory.o \
./logger.o \
./loggingappender.o \
./main.o \
./pluginbase.o \
./pluginsfactory.o \
./policy.o \
./policyengine.o \
./session.o \
./streamsession.o \
./trpsession.o 

CPP_DEPS += \
./adaptationmanager.d \
./consoleappender.d \
./event.d \
./eventtype.d \
./facade.d \
./gsck.d \
./infrafactory.d \
./logger.d \
./loggingappender.d \
./main.d \
./pluginbase.d \
./pluginsfactory.d \
./policy.d \
./policyengine.d \
./session.d \
./streamsession.d \
./trpsession.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/ivocalado/workspace/streamadapt/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


