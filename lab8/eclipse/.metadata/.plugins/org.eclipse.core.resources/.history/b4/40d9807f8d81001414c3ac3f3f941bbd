################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bitmask.c \
../src/collisions.c \
../src/drawing.c \
../src/fraps.c \
../src/movements.c \
../src/platform.c \
../src/utils.c \
../src/vdmaTest.c \
../src/xac97_l.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/bitmask.o \
./src/collisions.o \
./src/drawing.o \
./src/fraps.o \
./src/movements.o \
./src/platform.o \
./src/utils.o \
./src/vdmaTest.o \
./src/xac97_l.o 

C_DEPS += \
./src/bitmask.d \
./src/collisions.d \
./src/drawing.d \
./src/fraps.d \
./src/movements.d \
./src/platform.d \
./src/utils.d \
./src/vdmaTest.d \
./src/xac97_l.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O3 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


