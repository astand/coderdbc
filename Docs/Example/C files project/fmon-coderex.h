// Generated at @Tuesday, 28 July, 2020 20:29:13. Ver: 0.1

#pragma once


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "canmonitorutil.h"

// This file contains the prototypes of all the functions that will be called
// from each Unpack_*name* function to detect DBC related errors
// It is the user responsibility to defined these functions in the
// separated .c file. If it won't be done the linkage error will happen
void FMon_ABS11_coderEx(FrameMonitor_t * _mon); 
void FMon_ACU13_coderEx(FrameMonitor_t * _mon); 
void FMon_CAL_SAS11_coderEx(FrameMonitor_t * _mon); 
void FMon_CGW5_coderEx(FrameMonitor_t * _mon); 
void FMon_DATC11_coderEx(FrameMonitor_t * _mon); 
void FMon_DATC12_coderEx(FrameMonitor_t * _mon); 
void FMon_DATC13_coderEx(FrameMonitor_t * _mon); 
void FMon_DATC14_coderEx(FrameMonitor_t * _mon); 
void FMon_EMS_DCT11_coderEx(FrameMonitor_t * _mon); 
void FMon_EMS_DCT12_coderEx(FrameMonitor_t * _mon); 
void FMon_EMS18_coderEx(FrameMonitor_t * _mon); 
void FMon_ESP11_coderEx(FrameMonitor_t * _mon); 
void FMon_ESP12_coderEx(FrameMonitor_t * _mon); 
void FMon_FCA11_coderEx(FrameMonitor_t * _mon); 
void FMon_SCC11_coderEx(FrameMonitor_t * _mon); 
void FMon_SCC12_coderEx(FrameMonitor_t * _mon); 
void FMon_SCC13_coderEx(FrameMonitor_t * _mon); 
void FMon_SCC14_coderEx(FrameMonitor_t * _mon); 
void FMon_SPAS11_coderEx(FrameMonitor_t * _mon); 
void FMon_SPAS12_coderEx(FrameMonitor_t * _mon); 
void FMon_TCS11_coderEx(FrameMonitor_t * _mon); 
void FMon_TCS12_coderEx(FrameMonitor_t * _mon); 
void FMon_TCS13_coderEx(FrameMonitor_t * _mon); 
void FMon_TCS15_coderEx(FrameMonitor_t * _mon); 
void FMon_TCU_DCT13_coderEx(FrameMonitor_t * _mon); 
void FMon_TCU11_coderEx(FrameMonitor_t * _mon); 
void FMon_TCU12_coderEx(FrameMonitor_t * _mon); 
void FMon_TCU13_coderEx(FrameMonitor_t * _mon); 
void FMon_VSM11_coderEx(FrameMonitor_t * _mon); 
void FMon_WHL_SPD11_coderEx(FrameMonitor_t * _mon); 

#ifdef __cplusplus
}
#endif

