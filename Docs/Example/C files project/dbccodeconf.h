#pragma once

#include <stdint.h>

// As in the expample program generation setting 
// <UseCANFrame> was set to 1 then __CoderDbcCanFrame_t__
// must be defined. 

// minimal struct is CanRxFrame
typedef struct {
	uint32_t MsgId : 29;
	uint32_t IDE : 1;
	
	uint8_t DLC;
	uint8_t Data[8];
} CanRxFrame;

typedef CanRxFrame __CoderDbcCanFrame_t__;

// This is also the place to enable util TX and RX struct like this (look at the *_binUtil.* files)
#define __DEF_CODEREX__


