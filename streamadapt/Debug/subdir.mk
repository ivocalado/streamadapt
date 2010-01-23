################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../adaptationmanager.cpp \
../consoleappender.cpp \
../event.cpp \
../eventregister.cpp \
../eventtype.cpp \
../facade.cpp \
../gsck.cpp \
../infrafactory.cpp \
../jobmanager.cpp \
../logger.cpp \
../loggingappender.cpp \
../pluginbase.cpp \
../pluginsfactory.cpp \
../policy.cpp \
../policyengine.cpp \
../session.cpp \
../sessionmanager.cpp \
../streamsession.cpp \
../trpsession.cpp 

OBJS += \
./adaptationmanager.o \
./consoleappender.o \
./event.o \
./eventregister.o \
./eventtype.o \
./facade.o \
./gsck.o \
./infrafactory.o \
./jobmanager.o \
./logger.o \
./loggingappender.o \
./pluginbase.o \
./pluginsfactory.o \
./policy.o \
./policyengine.o \
./session.o \
./sessionmanager.o \
./streamsession.o \
./trpsession.o 

CPP_DEPS += \
./adaptationmanager.d \
./consoleappender.d \
./event.d \
./eventregister.d \
./eventtype.d \
./facade.d \
./gsck.d \
./infrafactory.d \
./jobmanager.d \
./logger.d \
./loggingappender.d \
./pluginbase.d \
./pluginsfactory.d \
./policy.d \
./policyengine.d \
./session.d \
./sessionmanager.d \
./streamsession.d \
./trpsession.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/ivocalado/workspace/streamadapt/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


