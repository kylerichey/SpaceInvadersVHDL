##############################################################################
## Filename:          C:\NEK\lab8\SpaceInvaderTestHW2/drivers/fraps_v1_00_b/data/fraps_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Tue Dec 09 17:21:28 2014 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "fraps" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
