# TCL File Generated by Component Editor 17.1
# Fri Dec 03 14:12:12 CET 2021
# DO NOT MODIFY


# 
# modMultiPWMDriver "modMultiPWMDriver" v1.0
#  2021.12.03.14:12:12
# create multi pwm signal
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module modMultiPWMDriver
# 
set_module_property DESCRIPTION "create multi pwm signal"
set_module_property NAME modMultiPWMDriver
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME modMultiPWMDriver
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL modMultiPWMComponent
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file modMultiPWM.v VERILOG PATH hardware/modMultiPWM.v
add_fileset_file modMultiPWMComponent.v VERILOG PATH hardware/modMultiPWMComponent.v TOP_LEVEL_FILE
add_fileset_file modPWM.v VERILOG PATH hardware/modPWM.v


# 
# parameters
# 
add_parameter NB_PWM INTEGER 24
set_parameter_property NB_PWM DEFAULT_VALUE 24
set_parameter_property NB_PWM DISPLAY_NAME NB_PWM
set_parameter_property NB_PWM TYPE INTEGER
set_parameter_property NB_PWM UNITS None
set_parameter_property NB_PWM ALLOWED_RANGES -2147483648:2147483647
set_parameter_property NB_PWM HDL_PARAMETER true
add_parameter RESOLUTION INTEGER 10
set_parameter_property RESOLUTION DEFAULT_VALUE 10
set_parameter_property RESOLUTION DISPLAY_NAME RESOLUTION
set_parameter_property RESOLUTION TYPE INTEGER
set_parameter_property RESOLUTION UNITS None
set_parameter_property RESOLUTION ALLOWED_RANGES -2147483648:2147483647
set_parameter_property RESOLUTION HDL_PARAMETER true


# 
# display items
# 


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset_n reset_n Input 1


# 
# connection point avalon_slave_0
# 
add_interface avalon_slave_0 avalon end
set_interface_property avalon_slave_0 addressUnits WORDS
set_interface_property avalon_slave_0 associatedClock clock
set_interface_property avalon_slave_0 associatedReset reset
set_interface_property avalon_slave_0 bitsPerSymbol 8
set_interface_property avalon_slave_0 burstOnBurstBoundariesOnly false
set_interface_property avalon_slave_0 burstcountUnits WORDS
set_interface_property avalon_slave_0 explicitAddressSpan 0
set_interface_property avalon_slave_0 holdTime 0
set_interface_property avalon_slave_0 linewrapBursts false
set_interface_property avalon_slave_0 maximumPendingReadTransactions 0
set_interface_property avalon_slave_0 maximumPendingWriteTransactions 0
set_interface_property avalon_slave_0 readLatency 0
set_interface_property avalon_slave_0 readWaitTime 1
set_interface_property avalon_slave_0 setupTime 0
set_interface_property avalon_slave_0 timingUnits Cycles
set_interface_property avalon_slave_0 writeWaitTime 0
set_interface_property avalon_slave_0 ENABLED true
set_interface_property avalon_slave_0 EXPORT_OF ""
set_interface_property avalon_slave_0 PORT_NAME_MAP ""
set_interface_property avalon_slave_0 CMSIS_SVD_VARIABLES ""
set_interface_property avalon_slave_0 SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave_0 chipselect chipselect Input 1
add_interface_port avalon_slave_0 write_n write_n Input 1
add_interface_port avalon_slave_0 writedata writedata Input 32
add_interface_port avalon_slave_0 address address Input 2
add_interface_port avalon_slave_0 clkOutPWM writeresponsevalid_n Output 1
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isPrintableDevice 0


# 
# connection point PWM
# 
add_interface PWM conduit end
set_interface_property PWM associatedClock clock
set_interface_property PWM associatedReset ""
set_interface_property PWM ENABLED true
set_interface_property PWM EXPORT_OF ""
set_interface_property PWM PORT_NAME_MAP ""
set_interface_property PWM CMSIS_SVD_VARIABLES ""
set_interface_property PWM SVD_ADDRESS_GROUP ""

add_interface_port PWM PWM export Output 24


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock CMSIS_SVD_VARIABLES ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clk clk Input 1


# 
# connection point clkInPWM
# 
add_interface clkInPWM clock end
set_interface_property clkInPWM clockRate 0
set_interface_property clkInPWM ENABLED true
set_interface_property clkInPWM EXPORT_OF ""
set_interface_property clkInPWM PORT_NAME_MAP ""
set_interface_property clkInPWM CMSIS_SVD_VARIABLES ""
set_interface_property clkInPWM SVD_ADDRESS_GROUP ""

add_interface_port clkInPWM clkInPWM clk Input 1


# 
# connection point clkOutPWM
# 
add_interface clkOutPWM conduit end
set_interface_property clkOutPWM associatedClock clock
set_interface_property clkOutPWM associatedReset ""
set_interface_property clkOutPWM ENABLED true
set_interface_property clkOutPWM EXPORT_OF ""
set_interface_property clkOutPWM PORT_NAME_MAP ""
set_interface_property clkOutPWM CMSIS_SVD_VARIABLES ""
set_interface_property clkOutPWM SVD_ADDRESS_GROUP ""

add_interface_port clkOutPWM clkOutPWM export Output 1

