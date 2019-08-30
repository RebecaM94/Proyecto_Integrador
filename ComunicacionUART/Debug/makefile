################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

-include makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include synergy/ssp/src/driver/r_sci_uart/subdir.mk
-include synergy/ssp/src/driver/r_ioport/subdir.mk
-include synergy/ssp/src/driver/r_icu/subdir.mk
-include synergy/ssp/src/driver/r_fmi/subdir.mk
-include synergy/ssp/src/driver/r_elc/subdir.mk
-include synergy/ssp/src/driver/r_dtc/subdir.mk
-include synergy/ssp/src/driver/r_cgc/hw/subdir.mk
-include synergy/ssp/src/driver/r_cgc/subdir.mk
-include synergy/ssp/src/bsp/mcu/s7g2/subdir.mk
-include synergy/ssp/src/bsp/mcu/all/subdir.mk
-include synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/subdir.mk
-include synergy/board/s7g2_sk/subdir.mk
-include src/synergy_gen/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
ComunicacionUART.srec \

SECONDARY_SIZE += \
ComunicacionUART.siz \


# All Target
all: ComunicacionUART.elf secondary-outputs

# Tool invocations
ComunicacionUART.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	$(file > ComunicacionUART.elf.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -T "C:\\Users\\SEI103\\Documents\\SuperTeam\\ComunicacionUART\\script\\S7G2.ld" -Xlinker --gc-sections -L "C:\\Users\\SEI103\\Documents\\SuperTeam\\ComunicacionUART\\synergy\\ssp\\src\\bsp\\cmsis\\DSP_Lib\\cm4_gcc" -Wl,-Map,"ComunicacionUART.map" --specs=nano.specs --specs=rdimon.specs -o "ComunicacionUART.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--end-group)
	arm-none-eabi-gcc @"ComunicacionUART.elf.in"
	@echo 'Finished building target: $@'
	@echo ' '

ComunicacionUART.srec: ComunicacionUART.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O srec "ComunicacionUART.elf"  "ComunicacionUART.srec"
	@echo 'Finished building: $@'
	@echo ' '

ComunicacionUART.siz: ComunicacionUART.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "ComunicacionUART.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
ifneq ($(strip $(OBJS)),)
	-$(file > clean_OBJS.tmp, $(OBJS))
	-@ xargs -s 6000 -t -a clean_OBJS.tmp $(RM)
	-@$(RM) clean_OBJS.tmp
endif
ifneq ($(strip $(SECONDARY_FLASH)),)
	-$(file > clean_SECONDARY_FLASH.tmp, $(SECONDARY_FLASH))
	-@ xargs -s 6000 -t -a clean_SECONDARY_FLASH.tmp $(RM)
	-@$(RM) clean_SECONDARY_FLASH.tmp
endif
ifneq ($(strip $(SECONDARY_SIZE)),)
	-$(file > clean_SECONDARY_SIZE.tmp, $(SECONDARY_SIZE))
	-@ xargs -s 6000 -t -a clean_SECONDARY_SIZE.tmp $(RM)
	-@$(RM) clean_SECONDARY_SIZE.tmp
endif
ifneq ($(strip $(ASM_DEPS)),)
	-$(file > clean_ASM_DEPS.tmp, $(ASM_DEPS))
	-@ xargs -s 6000 -t -a clean_ASM_DEPS.tmp $(RM)
	-@$(RM) clean_ASM_DEPS.tmp
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
	-$(file > clean_S_UPPER_DEPS.tmp, $(S_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_S_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_S_UPPER_DEPS.tmp
endif
ifneq ($(strip $(C_DEPS)),)
	-$(file > clean_C_DEPS.tmp, $(C_DEPS))
	-@ xargs -s 6000 -t -a clean_C_DEPS.tmp $(RM)
	-@$(RM) clean_C_DEPS.tmp
endif
	-$(RM)  ComunicacionUART.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
