################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Librerie/TIME/Time.obj: ../Librerie/TIME/Time.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" -g --gcc --define="ccs" --define=PART_LM3S9B92 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Librerie/TIME/Time.pp" --obj_directory="Librerie/TIME" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


