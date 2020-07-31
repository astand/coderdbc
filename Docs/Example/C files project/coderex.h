// Coder Example Main Files 

#pragma once


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// This file must define:
// base monitor struct
// function signature for CRC calculation
// function signature for getting system tick value (100 us step)
#include "canmonitorutil.h"


// UseCANFrame is checked!
// In this case the Pack_*name* function will take the pointer at
// @__CoderDbcCanFrame_t__ data struct and the user must define this 
// type. The best way is to define it (or typedef if already exists)
// the CANFrame type with fields:
//        -- MsgId : uint32_t
//        -- DLC : uint8_t
//        -- IDE : uint8_t
//        -- Data : uint8_t* (with minimum 8 bytes capacity)

// Do it in the common dbc config file
#include "dbccodeconf.h"


// def @ACU13 CAN Message (16)
#define ACU13_IDE (0U)
#define ACU13_DLC (8U)
#define ACU13_CANID (0x10U)
typedef struct
{

  uint8_t CF_Acu_CshAct;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     
  FrameMonitor_t mon1;
} ACU13_t;

// def @EMS18 CAN Message (48)
#define EMS18_IDE (0U)
#define EMS18_DLC (6U)
#define EMS18_CANID (0x30U)
// signal: @CR_Ems_DutyCyc1MSV
#define EMS18_CR_Ems_DutyCyc1MSV_CovFactor (0.1953)
// conversion value to CAN signal
#define EMS18_CR_Ems_DutyCyc1MSV_toS(x) ((uint8_t)((x) / 0.1953))
// conversion value from CAN signal
#define EMS18_CR_Ems_DutyCyc1MSV_fromS(x) ((x) * 0.1953)

// signal: @CR_Ems_DutyCyc2MSV
#define EMS18_CR_Ems_DutyCyc2MSV_CovFactor (0.13725)
// conversion value to CAN signal
#define EMS18_CR_Ems_DutyCyc2MSV_toS(x) ((uint8_t)((x) / 0.13725))
// conversion value from CAN signal
#define EMS18_CR_Ems_DutyCyc2MSV_fromS(x) ((x) * 0.13725)

// signal: @CR_Ems_DutyCyc3MSV
#define EMS18_CR_Ems_DutyCyc3MSV_CovFactor (0.392)
// conversion value to CAN signal
#define EMS18_CR_Ems_DutyCyc3MSV_toS(x) ((uint8_t)((x) / 0.392))
// conversion value from CAN signal
#define EMS18_CR_Ems_DutyCyc3MSV_fromS(x) ((x) * 0.392)

typedef struct
{

  uint8_t CF_Ems_DC1NumPerMSV;              //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint16_t CF_Ems_DC2NumPerMSV;             //      Bits=16.  [ 0     , 65535  ]  Unit:''     

  uint8_t CR_Ems_DutyCyc1MSV;               //      Bits=08.  [ 0     , 49.8   ]  Unit:'%'     Factor= 0.1953

  uint8_t CR_Ems_DutyCyc2MSV;               //      Bits=08.  [ 0     , 35     ]  Unit:'%'     Factor= 0.13725

  uint8_t CR_Ems_DutyCyc3MSV;               //      Bits=08.  [ 0     , 100    ]  Unit:'%'     Factor= 0.392 
  FrameMonitor_t mon1;
} EMS18_t;

// def @DATC14 CAN Message (64)
#define DATC14_IDE (0U)
#define DATC14_DLC (8U)
#define DATC14_CANID (0x40U)
// signal: @CR_Datc_SelfDiagCode
#define DATC14_CR_Datc_SelfDiagCode_CovFactor (1)
// conversion value to CAN signal
#define DATC14_CR_Datc_SelfDiagCode_toS(x) ((int16_t)((x) + 1))
// conversion value from CAN signal
#define DATC14_CR_Datc_SelfDiagCode_fromS(x) ((x))

typedef struct
{

  uint8_t CF_Datc_AqsLevelOut;              //      Bits=04.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_DiagMode;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  int16_t CR_Datc_SelfDiagCode;             //      Bits=08.  [ 0     , 254    ]  Unit:''      Offset= -1       

  uint8_t DATC_SyncDisp;                    //      Bits=04.  [ 0     , 3      ]  Unit:''     

  uint8_t DATC_OffDisp;                     //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t DATC_SmartVentDisp;               //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t DATC_SmartVentOnOffStatus;        //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t DATC_AutoDefogSysOff_Disp;        //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t DATC_ADSDisp;                     //      Bits=02.  [ 0     , 3      ]  Unit:''     
  FrameMonitor_t mon1;
} DATC14_t;

// def @DATC12 CAN Message (66)
#define DATC12_IDE (0U)
#define DATC12_DLC (8U)
#define DATC12_CANID (0x42U)
// signal: @CR_Datc_DrTempDispC
#define DATC12_CR_Datc_DrTempDispC_CovFactor (0.5)
// conversion value to CAN signal
#define DATC12_CR_Datc_DrTempDispC_toS(x) ((uint16_t)((x) / 0.5 - 28))
// conversion value from CAN signal
#define DATC12_CR_Datc_DrTempDispC_fromS(x) ((x) * 0.5)

// signal: @CR_Datc_DrTempDispF
#define DATC12_CR_Datc_DrTempDispF_CovFactor (1)
// conversion value to CAN signal
#define DATC12_CR_Datc_DrTempDispF_toS(x) ((uint16_t)((x) - 56))
// conversion value from CAN signal
#define DATC12_CR_Datc_DrTempDispF_fromS(x) ((x))

// signal: @CR_Datc_PsTempDispC
#define DATC12_CR_Datc_PsTempDispC_CovFactor (0.5)
// conversion value to CAN signal
#define DATC12_CR_Datc_PsTempDispC_toS(x) ((uint16_t)((x) / 0.5 - 28))
// conversion value from CAN signal
#define DATC12_CR_Datc_PsTempDispC_fromS(x) ((x) * 0.5)

// signal: @CR_Datc_PsTempDispF
#define DATC12_CR_Datc_PsTempDispF_CovFactor (1)
// conversion value to CAN signal
#define DATC12_CR_Datc_PsTempDispF_toS(x) ((uint16_t)((x) - 56))
// conversion value from CAN signal
#define DATC12_CR_Datc_PsTempDispF_fromS(x) ((x))

// signal: @CR_Datc_RearDrTempDispC
#define DATC12_CR_Datc_RearDrTempDispC_CovFactor (0.5)
// conversion value to CAN signal
#define DATC12_CR_Datc_RearDrTempDispC_toS(x) ((uint16_t)((x) / 0.5 - 28))
// conversion value from CAN signal
#define DATC12_CR_Datc_RearDrTempDispC_fromS(x) ((x) * 0.5)

// signal: @CR_Datc_RearDrTempDispF
#define DATC12_CR_Datc_RearDrTempDispF_CovFactor (1)
// conversion value to CAN signal
#define DATC12_CR_Datc_RearDrTempDispF_toS(x) ((uint16_t)((x) - 58))
// conversion value from CAN signal
#define DATC12_CR_Datc_RearDrTempDispF_fromS(x) ((x))

typedef struct
{

  uint16_t CR_Datc_DrTempDispC;             //      Bits=08.  [ 15    , 32     ]  Unit:'deg'   Offset= 14        Factor= 0.5   

  uint16_t CR_Datc_DrTempDispF;             //      Bits=08.  [ 58    , 90     ]  Unit:'deg'   Offset= 56       

  uint16_t CR_Datc_PsTempDispC;             //      Bits=08.  [ 15    , 32     ]  Unit:'deg'   Offset= 14        Factor= 0.5   

  uint16_t CR_Datc_PsTempDispF;             //      Bits=08.  [ 58    , 90     ]  Unit:'deg'   Offset= 56       

  uint16_t CR_Datc_RearDrTempDispC;         //      Bits=08.  [ 15    , 32     ]  Unit:'deg'   Offset= 14        Factor= 0.5   

  uint16_t CR_Datc_RearDrTempDispF;         //      Bits=08.  [ 58    , 90     ]  Unit:'deg'   Offset= 58       

  uint8_t CF_Datc_CO2_Warning;              //      Bits=08.  [ 0     , 3      ]  Unit:''     
  FrameMonitor_t mon1;
} DATC12_t;

// def @DATC13 CAN Message (67)
#define DATC13_IDE (0U)
#define DATC13_DLC (8U)
#define DATC13_CANID (0x43U)
typedef struct
{

  uint8_t CF_Datc_TempDispUnit;             //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_ModDisp;                  //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Datc_IonClean;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_ChgReqDisp;               //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_IntakeDisp;               //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_AutoDisp;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_FrDefLed;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_AutoDefogBlink;           //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_ClmScanDisp;              //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_AqsDisp;                  //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_AcDisp;                   //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_OpSts;                    //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Mtc_MaxAcDisp;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_DualDisp;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_PwrInf;                   //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Datc_RearManual;               //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_RearAutoDisp;             //      Bits=02.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Datc_RearOffDisp;              //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_RearClimateScnDisp;       //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_RearChgReqDisp;           //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Datc_RearModDisp;              //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Datc_RearBlwDisp;              //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Datc_PSModDisp;                //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Datc_FrontBlwDisp;             //      Bits=04.  [ 0     , 15     ]  Unit:''     
  FrameMonitor_t mon1;
} DATC13_t;

// def @DATC11 CAN Message (68)
#define DATC11_IDE (0U)
#define DATC11_DLC (8U)
#define DATC11_CANID (0x44U)
// signal: @CR_Datc_OutTempC
#define DATC11_CR_Datc_OutTempC_CovFactor (0.5)
// conversion value to CAN signal
#define DATC11_CR_Datc_OutTempC_toS(x) ((int16_t)((x) / 0.5 + 82))
// conversion value from CAN signal
#define DATC11_CR_Datc_OutTempC_fromS(x) ((x) * 0.5)

// signal: @CR_Datc_OutTempF
#define DATC11_CR_Datc_OutTempF_CovFactor (1)
// conversion value to CAN signal
#define DATC11_CR_Datc_OutTempF_toS(x) ((int16_t)((x) + 42))
// conversion value from CAN signal
#define DATC11_CR_Datc_OutTempF_fromS(x) ((x))

// signal: @CF_Datc_IncarTemp
#define DATC11_CF_Datc_IncarTemp_CovFactor (0.5)
// conversion value to CAN signal
#define DATC11_CF_Datc_IncarTemp_toS(x) ((int16_t)((x) / 0.5 + 80))
// conversion value from CAN signal
#define DATC11_CF_Datc_IncarTemp_fromS(x) ((x) * 0.5)

typedef struct
{

  uint8_t CF_Datc_Type;                     //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t CF_Datc_VerMaj;                   //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t CF_Datc_VerMin;                   //      Bits=08.  [ 0     , 255    ]  Unit:''     

  int16_t CR_Datc_OutTempC;                 //      Bits=08.  [ -41   , 86.5   ]  Unit:'deg'   Offset= -41       Factor= 0.5   

  int16_t CR_Datc_OutTempF;                 //      Bits=08.  [ -42   , 213    ]  Unit:'deg'   Offset= -42      

  int16_t CF_Datc_IncarTemp;                //      Bits=08.  [ -40   , 60     ]  Unit:'deg'   Offset= -40       Factor= 0.5   
  FrameMonitor_t mon1;
} DATC11_t;

// def @CGW5 CAN Message (127)
#define CGW5_IDE (0U)
#define CGW5_DLC (8U)
#define CGW5_CANID (0x7FU)
typedef struct
{

  uint8_t C_StopLampLhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_StopLampRhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_HMSLOpenSts;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_HLampLowLhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_HLampLowRhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_HLampHighLhOpenSts;             //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_HLampHighRhOpenSts;             //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_DRLLampLhOpenSts;               //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_DRLLampRhOpenSts;               //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_RearFOGLhOpenSts;               //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_RearFOGRhOpenSts;               //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_FrontFOGLhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_FrontFOGRhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_RearEXTTailLhOpenSts;           //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_RearEXTTailRhOpenSts;           //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_FrontEXTTailLhOpenSts;          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_FrontEXTTailRhOpenSts;          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_RearTSIGLhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_RearTSIGRhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_FrontTSIGLhOpenSts;             //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_FrontTSIGRhOpenSts;             //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_SBendingLhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_SBendingRhOpenSts;              //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_LicensePlateLhOpenSts;          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t C_LicensePlateRhOpenSts;          //      Bits=01.  [ 0     , 1      ]  Unit:''     
  FrameMonitor_t mon1;
} CGW5_t;

// def @EMS_DCT11 CAN Message (128)
#define EMS_DCT11_IDE (0U)
#define EMS_DCT11_DLC (8U)
#define EMS_DCT11_CANID (0x80U)
// signal: @PV_AV_CAN
#define EMS_DCT11_PV_AV_CAN_CovFactor (0.3906)
// conversion value to CAN signal
#define EMS_DCT11_PV_AV_CAN_toS(x) ((uint8_t)((x) / 0.3906))
// conversion value from CAN signal
#define EMS_DCT11_PV_AV_CAN_fromS(x) ((x) * 0.3906)

// signal: @TQ_STND
#define EMS_DCT11_TQ_STND_CovFactor (10)
// conversion value to CAN signal
#define EMS_DCT11_TQ_STND_toS(x) ((uint8_t)((x) / 10))
// conversion value from CAN signal
#define EMS_DCT11_TQ_STND_fromS(x) ((x) * 10)

// signal: @N
#define EMS_DCT11_N_CovFactor (0.25)
// conversion value to CAN signal
#define EMS_DCT11_N_toS(x) ((uint16_t)((x) / 0.25))
// conversion value from CAN signal
#define EMS_DCT11_N_fromS(x) ((x) * 0.25)

// signal: @TQI_ACOR
#define EMS_DCT11_TQI_ACOR_CovFactor (0.390625)
// conversion value to CAN signal
#define EMS_DCT11_TQI_ACOR_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define EMS_DCT11_TQI_ACOR_fromS(x) ((x) * 0.390625)

// signal: @TQFR
#define EMS_DCT11_TQFR_CovFactor (0.390625)
// conversion value to CAN signal
#define EMS_DCT11_TQFR_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define EMS_DCT11_TQFR_fromS(x) ((x) * 0.390625)

// signal: @TQI
#define EMS_DCT11_TQI_CovFactor (0.390625)
// conversion value to CAN signal
#define EMS_DCT11_TQI_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define EMS_DCT11_TQI_fromS(x) ((x) * 0.390625)

typedef struct
{

  uint8_t PV_AV_CAN;                        //      Bits=08.  [ 0     , 99.603 ]  Unit:'%'     Factor= 0.3906

  uint8_t TQ_STND;                          //      Bits=06.  [ 0     , 630    ]  Unit:'Nm'    Factor= 10    

  uint8_t F_N_ENG;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t F_SUB_TQI;                        //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint16_t N;                               //      Bits=16.  [ 0     , 16383.75 ]  Unit:'rpm'   Factor= 0.25  

  uint8_t TQI_ACOR;                         //      Bits=08.  [ 0     , 99.6094 ]  Unit:'%'     Factor= 0.390625

  uint8_t TQFR;                             //      Bits=08.  [ 0     , 99.6094 ]  Unit:'%'     Factor= 0.390625

  uint8_t TQI;                              //      Bits=08.  [ 0     , 99.609375 ]  Unit:'%'     Factor= 0.390625

  uint8_t CF_Ems_Alive;                     //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Ems_ChkSum;                    //      Bits=04.  [ 0     , 15     ]  Unit:''     
  FrameMonitor_t mon1;
} EMS_DCT11_t;

// def @EMS_DCT12 CAN Message (129)
#define EMS_DCT12_IDE (0U)
#define EMS_DCT12_DLC (8U)
#define EMS_DCT12_CANID (0x81U)
// signal: @CR_Ems_SoakTimeExt
#define EMS_DCT12_CR_Ems_SoakTimeExt_CovFactor (5)
// conversion value to CAN signal
#define EMS_DCT12_CR_Ems_SoakTimeExt_toS(x) ((uint8_t)((x) / 5))
// conversion value from CAN signal
#define EMS_DCT12_CR_Ems_SoakTimeExt_fromS(x) ((x) * 5)

// signal: @CR_Ems_IndAirTemp
#define EMS_DCT12_CR_Ems_IndAirTemp_CovFactor (0.75)
// conversion value to CAN signal
#define EMS_DCT12_CR_Ems_IndAirTemp_toS(x) ((int16_t)((x) / 0.75 + 64))
// conversion value from CAN signal
#define EMS_DCT12_CR_Ems_IndAirTemp_fromS(x) ((x) * 0.75)

typedef struct
{

  uint8_t CR_Ems_SoakTimeExt;               //      Bits=06.  [ 0     , 315    ]  Unit:'Min'   Factor= 5     

  uint8_t BRAKE_ACT;                        //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Ems_EngOperStat;               //      Bits=08.  [ 0     , 255    ]  Unit:''     

  int16_t CR_Ems_IndAirTemp;                //      Bits=08.  [ -48   , 143.25 ]  Unit:'deg'   Offset= -48       Factor= 0.75  

  uint8_t CF_Ems_Alive2;                    //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Ems_ChkSum2;                   //      Bits=04.  [ 0     , 15     ]  Unit:''     
  FrameMonitor_t mon1;
} EMS_DCT12_t;

// def @TCU11 CAN Message (273)
#define TCU11_IDE (0U)
#define TCU11_DLC (8U)
#define TCU11_CANID (0x111U)
// signal: @TQI_TCU_INC
#define TCU11_TQI_TCU_INC_CovFactor (0.390625)
// conversion value to CAN signal
#define TCU11_TQI_TCU_INC_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define TCU11_TQI_TCU_INC_fromS(x) ((x) * 0.390625)

// signal: @TQI_TCU
#define TCU11_TQI_TCU_CovFactor (0.390625)
// conversion value to CAN signal
#define TCU11_TQI_TCU_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define TCU11_TQI_TCU_fromS(x) ((x) * 0.390625)

// signal: @TEMP_AT
#define TCU11_TEMP_AT_CovFactor (1)
// conversion value to CAN signal
#define TCU11_TEMP_AT_toS(x) ((int16_t)((x) + 40))
// conversion value from CAN signal
#define TCU11_TEMP_AT_fromS(x) ((x))

// signal: @N_TC
#define TCU11_N_TC_CovFactor (0.25)
// conversion value to CAN signal
#define TCU11_N_TC_toS(x) ((uint16_t)((x) / 0.25))
// conversion value from CAN signal
#define TCU11_N_TC_fromS(x) ((x) * 0.25)

typedef struct
{

  uint8_t TQI_TCU_INC;                      //      Bits=08.  [ 0     , 99.609375 ]  Unit:'%'     Factor= 0.390625

  uint8_t G_SEL_DISP;                       //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t F_TCU;                            //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t TCU_TYPE;                         //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t TCU_OBD;                          //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t SWI_GS;                           //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t GEAR_TYPE;                        //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t TQI_TCU;                          //      Bits=08.  [ 0     , 99.609375 ]  Unit:'%'     Factor= 0.390625

  int16_t TEMP_AT;                          //      Bits=08.  [ -40   , 214    ]  Unit:'deg'   Offset= -40      

  uint16_t N_TC;                            //      Bits=16.  [ 0     , 16383.5 ]  Unit:'rpm'   Factor= 0.25  

  uint8_t SWI_CC;                           //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Tcu_Alive1;                    //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Tcu_ChkSum1;                   //      Bits=04.  [ 0     , 15     ]  Unit:''     
  FrameMonitor_t mon1;
} TCU11_t;

// def @TCU12 CAN Message (274)
#define TCU12_IDE (0U)
#define TCU12_DLC (8U)
#define TCU12_CANID (0x112U)
// signal: @ETL_TCU
#define TCU12_ETL_TCU_CovFactor (2)
// conversion value to CAN signal
#define TCU12_ETL_TCU_toS(x) ((uint8_t)((x) / 2))
// conversion value from CAN signal
#define TCU12_ETL_TCU_fromS(x) ((x) * 2)

// signal: @SPK_RTD_TCU
#define TCU12_SPK_RTD_TCU_CovFactor (0.375)
// conversion value to CAN signal
#define TCU12_SPK_RTD_TCU_toS(x) ((int16_t)((x) / 0.375 + 63))
// conversion value from CAN signal
#define TCU12_SPK_RTD_TCU_fromS(x) ((x) * 0.375)

// signal: @N_TC_RAW
#define TCU12_N_TC_RAW_CovFactor (0.25)
// conversion value to CAN signal
#define TCU12_N_TC_RAW_toS(x) ((uint16_t)((x) / 0.25))
// conversion value from CAN signal
#define TCU12_N_TC_RAW_fromS(x) ((x) * 0.25)

// signal: @VS_TCU_DECIMAL
#define TCU12_VS_TCU_DECIMAL_CovFactor (0.0078125)
// conversion value to CAN signal
#define TCU12_VS_TCU_DECIMAL_toS(x) ((uint8_t)((x) / 0.0078125))
// conversion value from CAN signal
#define TCU12_VS_TCU_DECIMAL_fromS(x) ((x) * 0.0078125)

typedef struct
{

  uint8_t ETL_TCU;                          //      Bits=08.  [ 0     , 508    ]  Unit:'Nm'    Factor= 2     

  uint8_t CUR_GR;                           //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Tcu_Alive;                     //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Tcu_ChkSum;                    //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t VS_TCU;                           //      Bits=08.  [ 0     , 254    ]  Unit:'km/h' 

  uint8_t FUEL_CUT_TCU;                     //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t INH_FUEL_CUT;                     //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t IDLE_UP_TCU;                      //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t N_INC_TCU;                        //      Bits=01.  [ 0     , 1      ]  Unit:''     

  int16_t SPK_RTD_TCU;                      //      Bits=08.  [ -15   , 15     ]  Unit:''      Offset= -23.625   Factor= 0.375 

  uint16_t N_TC_RAW;                        //      Bits=16.  [ 0     , 16383.5 ]  Unit:'rpm'   Factor= 0.25  

  uint8_t VS_TCU_DECIMAL;                   //      Bits=08.  [ 0     , 0.9921875 ]  Unit:'km/h'  Factor= 0.0078125
  FrameMonitor_t mon1;
} TCU12_t;

// def @TCU13 CAN Message (275)
#define TCU13_IDE (0U)
#define TCU13_DLC (8U)
#define TCU13_CANID (0x113U)
// signal: @N_TGT_LUP
#define TCU13_N_TGT_LUP_CovFactor (10)
// conversion value to CAN signal
#define TCU13_N_TGT_LUP_toS(x) ((uint16_t)((x) / 10 - 50))
// conversion value from CAN signal
#define TCU13_N_TGT_LUP_fromS(x) ((x) * 10)

// signal: @SLOPE_TCU
#define TCU13_SLOPE_TCU_CovFactor (0.5)
// conversion value to CAN signal
#define TCU13_SLOPE_TCU_toS(x) ((int8_t)((x) / 0.5 + 32))
// conversion value from CAN signal
#define TCU13_SLOPE_TCU_fromS(x) ((x) * 0.5)

// signal: @CF_Tcu_TqGrdLim
#define TCU13_CF_Tcu_TqGrdLim_CovFactor (10)
// conversion value to CAN signal
#define TCU13_CF_Tcu_TqGrdLim_toS(x) ((uint8_t)((x) / 10))
// conversion value from CAN signal
#define TCU13_CF_Tcu_TqGrdLim_fromS(x) ((x) * 10)

// signal: @CR_Tcu_IsgTgtRPM
#define TCU13_CR_Tcu_IsgTgtRPM_CovFactor (20)
// conversion value to CAN signal
#define TCU13_CR_Tcu_IsgTgtRPM_toS(x) ((uint8_t)((x) / 20))
// conversion value from CAN signal
#define TCU13_CR_Tcu_IsgTgtRPM_fromS(x) ((x) * 20)

typedef struct
{

  uint16_t N_TGT_LUP;                       //      Bits=08.  [ 500   , 3040   ]  Unit:'rpm'   Offset= 500       Factor= 10    

  int8_t SLOPE_TCU;                         //      Bits=06.  [ -16   , 15.5   ]  Unit:'%'     Offset= -16       Factor= 0.5   

  uint8_t CF_Tcu_InhCda;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Tcu_IsgInhib;                  //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Tcu_BkeOnReq;                  //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Tcu_NCStat;                    //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Tcu_TarGr;                     //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Tcu_ShfPatt;                   //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Tcu_InhVis;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Tcu_PRelReq;                   //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Tcu_ITPhase;                   //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Tcu_ActEcoRdy;                 //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Tcu_TqGrdLim;                  //      Bits=08.  [ 0     , 2540   ]  Unit:'Nm/s'  Factor= 10    

  uint8_t CR_Tcu_IsgTgtRPM;                 //      Bits=08.  [ 0     , 3500   ]  Unit:'rpm'   Factor= 20    

  uint8_t CF_Tcu_SptRdy;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Tcu_SbwPInfo;                  //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Tcu_Alive3;                    //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Tcu_ChkSum3;                   //      Bits=04.  [ 0     , 15     ]  Unit:''     
  FrameMonitor_t mon1;
} TCU13_t;

// def @TCS11 CAN Message (339)
#define TCS11_IDE (0U)
#define TCS11_DLC (8U)
#define TCS11_CANID (0x153U)
// signal: @TQI_TCS
#define TCS11_TQI_TCS_CovFactor (0.390625)
// conversion value to CAN signal
#define TCS11_TQI_TCS_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define TCS11_TQI_TCS_fromS(x) ((x) * 0.390625)

// signal: @TQI_MSR
#define TCS11_TQI_MSR_CovFactor (0.390625)
// conversion value to CAN signal
#define TCS11_TQI_MSR_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define TCS11_TQI_MSR_fromS(x) ((x) * 0.390625)

// signal: @TQI_SLW_TCS
#define TCS11_TQI_SLW_TCS_CovFactor (0.390625)
// conversion value to CAN signal
#define TCS11_TQI_SLW_TCS_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define TCS11_TQI_SLW_TCS_fromS(x) ((x) * 0.390625)

typedef struct
{

  uint8_t TCS_REQ;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t MSR_C_REQ;                        //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t TCS_PAS;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t TCS_GSC;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Esc_LimoInfo;                  //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t ABS_DIAG;                         //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ABS_DEF;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t TCS_DEF;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t TCS_CTL;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ABS_ACT;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t EBD_DEF;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ESP_PAS;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ESP_DEF;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ESP_CTL;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t TCS_MFRN;                         //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t DBC_CTL;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t DBC_PAS;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t DBC_DEF;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t HAC_CTL;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t HAC_PAS;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t HAC_DEF;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ESS_STAT;                         //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t TQI_TCS;                          //      Bits=08.  [ 0     , 99.609375 ]  Unit:'%'     Factor= 0.390625

  uint8_t TQI_MSR;                          //      Bits=08.  [ 0     , 99.609375 ]  Unit:'%'     Factor= 0.390625

  uint8_t TQI_SLW_TCS;                      //      Bits=08.  [ 0     , 99.609375 ]  Unit:'%'     Factor= 0.390625

  uint8_t CF_Esc_BrkCtl;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t BLA_CTL;                          //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t AliveCounter_TCS1;                //      Bits=04.  [ 0     , 14     ]  Unit:''     

  uint8_t CheckSum_TCS1;                    //      Bits=08.  [ 0     , 255    ]  Unit:''     
  FrameMonitor_t mon1;
} TCS11_t;

// def @TCU_DCT13 CAN Message (354)
#define TCU_DCT13_IDE (0U)
#define TCU_DCT13_DLC (3U)
#define TCU_DCT13_CANID (0x162U)
// signal: @Clutch_Driving_Tq
#define TCU_DCT13_Clutch_Driving_Tq_CovFactor (1)
// conversion value to CAN signal
#define TCU_DCT13_Clutch_Driving_Tq_toS(x) ((int16_t)((x) + 512))
// conversion value from CAN signal
#define TCU_DCT13_Clutch_Driving_Tq_fromS(x) ((x))

// signal: @Cluster_Engine_RPM
#define TCU_DCT13_Cluster_Engine_RPM_CovFactor (0.9766)
// conversion value to CAN signal
#define TCU_DCT13_Cluster_Engine_RPM_toS(x) ((uint16_t)((x) / 0.9766))
// conversion value from CAN signal
#define TCU_DCT13_Cluster_Engine_RPM_fromS(x) ((x) * 0.9766)

typedef struct
{

  int16_t Clutch_Driving_Tq;                //      Bits=10.  [ 0     , 0      ]  Unit:'Nm'    Offset= -512     

  uint16_t Cluster_Engine_RPM;              //      Bits=13.  [ 0     , 0      ]  Unit:''      Factor= 0.9766

  uint8_t Cluster_Engine_RPM_Flag;          //      Bits=01.  [ 0     , 0      ]  Unit:''     
  FrameMonitor_t mon1;
} TCU_DCT13_t;

// def @VSM11 CAN Message (356)
#define VSM11_IDE (0U)
#define VSM11_DLC (4U)
#define VSM11_CANID (0x164U)
// signal: @CR_Esc_StrTqReq
#define VSM11_CR_Esc_StrTqReq_CovFactor (0.01)
// conversion value to CAN signal
#define VSM11_CR_Esc_StrTqReq_toS(x) ((int16_t)((x) / 0.01 + 2048))
// conversion value from CAN signal
#define VSM11_CR_Esc_StrTqReq_fromS(x) ((x) * 0.01)

typedef struct
{

  int16_t CR_Esc_StrTqReq;                  //      Bits=12.  [ -20.48, 20.47  ]  Unit:'Nm'    Offset= -20.48    Factor= 0.01  

  uint8_t CF_Esc_Act;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Esc_CtrMode;                   //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Esc_Def;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Esc_AliveCnt;                  //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Esc_Chksum;                    //      Bits=08.  [ 0     , 255    ]  Unit:''     
  FrameMonitor_t mon1;
} VSM11_t;

// def @ESP12 CAN Message (544)
#define ESP12_IDE (0U)
#define ESP12_DLC (8U)
#define ESP12_CANID (0x220U)
// signal: @LAT_ACCEL
#define ESP12_LAT_ACCEL_CovFactor (0.01)
// conversion value to CAN signal
#define ESP12_LAT_ACCEL_toS(x) ((int16_t)((x) / 0.01 + 1023))
// conversion value from CAN signal
#define ESP12_LAT_ACCEL_fromS(x) ((x) * 0.01)

// signal: @LONG_ACCEL
#define ESP12_LONG_ACCEL_CovFactor (0.01)
// conversion value to CAN signal
#define ESP12_LONG_ACCEL_toS(x) ((int16_t)((x) / 0.01 + 1023))
// conversion value from CAN signal
#define ESP12_LONG_ACCEL_fromS(x) ((x) * 0.01)

// signal: @CYL_PRES
#define ESP12_CYL_PRES_CovFactor (0.1)
// conversion value to CAN signal
#define ESP12_CYL_PRES_toS(x) ((uint16_t)((x) / 0.1))
// conversion value from CAN signal
#define ESP12_CYL_PRES_fromS(x) ((x) * 0.1)

// signal: @YAW_RATE
#define ESP12_YAW_RATE_CovFactor (0.01)
// conversion value to CAN signal
#define ESP12_YAW_RATE_toS(x) ((int16_t)((x) / 0.01 + 4095))
// conversion value from CAN signal
#define ESP12_YAW_RATE_fromS(x) ((x) * 0.01)

typedef struct
{

  int16_t LAT_ACCEL;                        //      Bits=11.  [ -10.23, 10.24  ]  Unit:'m/s^2' Offset= -10.23    Factor= 0.01  

  uint8_t LAT_ACCEL_STAT;                   //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t LAT_ACCEL_DIAG;                   //      Bits=01.  [ 0     , 1      ]  Unit:''     

  int16_t LONG_ACCEL;                       //      Bits=11.  [ -10.23, 10.24  ]  Unit:'m/s^2' Offset= -10.23    Factor= 0.01  

  uint8_t LONG_ACCEL_STAT;                  //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t LONG_ACCEL_DIAG;                  //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint16_t CYL_PRES;                        //      Bits=12.  [ 0     , 409.5  ]  Unit:'Bar'   Factor= 0.1   

  uint8_t CYL_PRES_STAT;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CYL_PRESS_DIAG;                   //      Bits=01.  [ 0     , 1      ]  Unit:''     

  int16_t YAW_RATE;                         //      Bits=13.  [ -40.95, 40.96  ]  Unit:''      Offset= -40.95    Factor= 0.01  

  uint8_t YAW_RATE_STAT;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t YAW_RATE_DIAG;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ESP12_AliveCounter;               //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t ESP12_Checksum;                   //      Bits=04.  [ 0     , 15     ]  Unit:''     
  FrameMonitor_t mon1;
} ESP12_t;

// def @WHL_SPD11 CAN Message (902)
#define WHL_SPD11_IDE (0U)
#define WHL_SPD11_DLC (8U)
#define WHL_SPD11_CANID (0x386U)
// signal: @WHL_SPD_FL
#define WHL_SPD11_WHL_SPD_FL_CovFactor (0.03125)
// conversion value to CAN signal
#define WHL_SPD11_WHL_SPD_FL_toS(x) ((uint16_t)((x) / 0.03125))
// conversion value from CAN signal
#define WHL_SPD11_WHL_SPD_FL_fromS(x) ((x) * 0.03125)

// signal: @WHL_SPD_FR
#define WHL_SPD11_WHL_SPD_FR_CovFactor (0.03125)
// conversion value to CAN signal
#define WHL_SPD11_WHL_SPD_FR_toS(x) ((uint16_t)((x) / 0.03125))
// conversion value from CAN signal
#define WHL_SPD11_WHL_SPD_FR_fromS(x) ((x) * 0.03125)

// signal: @WHL_SPD_RL
#define WHL_SPD11_WHL_SPD_RL_CovFactor (0.03125)
// conversion value to CAN signal
#define WHL_SPD11_WHL_SPD_RL_toS(x) ((uint16_t)((x) / 0.03125))
// conversion value from CAN signal
#define WHL_SPD11_WHL_SPD_RL_fromS(x) ((x) * 0.03125)

// signal: @WHL_SPD_RR
#define WHL_SPD11_WHL_SPD_RR_CovFactor (0.03125)
// conversion value to CAN signal
#define WHL_SPD11_WHL_SPD_RR_toS(x) ((uint16_t)((x) / 0.03125))
// conversion value from CAN signal
#define WHL_SPD11_WHL_SPD_RR_fromS(x) ((x) * 0.03125)

typedef struct
{

  uint16_t WHL_SPD_FL;                      //      Bits=14.  [ 0     , 511.96875 ]  Unit:'km/h'  Factor= 0.03125

  uint8_t WHL_SPD_AliveCounter_LSB;         //      Bits=02.  [ 0     , 15     ]  Unit:''     

  uint16_t WHL_SPD_FR;                      //      Bits=14.  [ 0     , 511.96875 ]  Unit:'km/h'  Factor= 0.03125

  uint8_t WHL_SPD_AliveCounter_MSB;         //      Bits=02.  [ 0     , 15     ]  Unit:''     

  uint16_t WHL_SPD_RL;                      //      Bits=14.  [ 0     , 511.96875 ]  Unit:'km/h'  Factor= 0.03125

  uint8_t WHL_SPD_Checksum_LSB;             //      Bits=02.  [ 0     , 15     ]  Unit:''     

  uint16_t WHL_SPD_RR;                      //      Bits=14.  [ 0     , 511.96875 ]  Unit:'km/h'  Factor= 0.03125

  uint8_t WHL_SPD_Checksum_MSB;             //      Bits=02.  [ 0     , 15     ]  Unit:''     
  FrameMonitor_t mon1;
} WHL_SPD11_t;

// def @SCC14 CAN Message (905)
#define SCC14_IDE (0U)
#define SCC14_DLC (8U)
#define SCC14_CANID (0x389U)
// signal: @ComfortBandUpper
#define SCC14_ComfortBandUpper_CovFactor (0.02)
// conversion value to CAN signal
#define SCC14_ComfortBandUpper_toS(x) ((uint8_t)((x) / 0.02))
// conversion value from CAN signal
#define SCC14_ComfortBandUpper_fromS(x) ((x) * 0.02)

// signal: @ComfortBandLower
#define SCC14_ComfortBandLower_CovFactor (0.02)
// conversion value to CAN signal
#define SCC14_ComfortBandLower_toS(x) ((uint8_t)((x) / 0.02))
// conversion value from CAN signal
#define SCC14_ComfortBandLower_fromS(x) ((x) * 0.02)

// signal: @JerkUpperLimit
#define SCC14_JerkUpperLimit_CovFactor (0.1)
// conversion value to CAN signal
#define SCC14_JerkUpperLimit_toS(x) ((uint8_t)((x) / 0.1))
// conversion value from CAN signal
#define SCC14_JerkUpperLimit_fromS(x) ((x) * 0.1)

// signal: @JerkLowerLimit
#define SCC14_JerkLowerLimit_CovFactor (0.1)
// conversion value to CAN signal
#define SCC14_JerkLowerLimit_toS(x) ((uint8_t)((x) / 0.1))
// conversion value from CAN signal
#define SCC14_JerkLowerLimit_fromS(x) ((x) * 0.1)

typedef struct
{

  uint8_t ComfortBandUpper;                 //      Bits=06.  [ 0     , 1.26   ]  Unit:'m/s^2' Factor= 0.02  

  uint8_t ComfortBandLower;                 //      Bits=06.  [ 0     , 1.26   ]  Unit:'m/s^2' Factor= 0.02  

  uint8_t JerkUpperLimit;                   //      Bits=07.  [ 0     , 12.7   ]  Unit:'m/s^3' Factor= 0.1   

  uint8_t JerkLowerLimit;                   //      Bits=07.  [ 0     , 12.7   ]  Unit:'m/s^3' Factor= 0.1   

  uint8_t SCCMode;                          //      Bits=03.  [ 0     , 7      ]  Unit:''     
  FrameMonitor_t mon1;
} SCC14_t;

// def @ABS11 CAN Message (906)
#define ABS11_IDE (0U)
#define ABS11_DLC (8U)
#define ABS11_CANID (0x38AU)
typedef struct
{

  uint8_t ABS_DEF;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t EBD_DEF;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ABS_ACT;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ABS_W_LAMP;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t EBD_W_LAMP;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ABS_DIAG;                         //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ESS_STAT;                         //      Bits=02.  [ 0     , 3      ]  Unit:''     
  FrameMonitor_t mon1;
} ABS11_t;

// def @FCA11 CAN Message (909)
#define FCA11_IDE (0U)
#define FCA11_DLC (8U)
#define FCA11_CANID (0x38DU)
// signal: @CR_VSM_DecCmd
#define FCA11_CR_VSM_DecCmd_CovFactor (0.01)
// conversion value to CAN signal
#define FCA11_CR_VSM_DecCmd_toS(x) ((uint8_t)((x) / 0.01))
// conversion value from CAN signal
#define FCA11_CR_VSM_DecCmd_fromS(x) ((x) * 0.01)

typedef struct
{

  uint8_t CF_VSM_Prefill;                   //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_VSM_HBACmd;                    //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_VSM_Warn;                      //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_VSM_BeltCmd;                   //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CR_VSM_DecCmd;                    //      Bits=08.  [ 0     , 2.55   ]  Unit:'g'     Factor= 0.01  

  uint8_t FCA_Status;                       //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t FCA_CmdAct;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t FCA_StopReq;                      //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t FCA_DrvSetStatus;                 //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_VSM_DecCmdAct;                 //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t FCA_Failinfo;                     //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CR_FCA_Alive;                     //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CR_FCA_ChkSum;                    //      Bits=04.  [ 0     , 15     ]  Unit:''     
  FrameMonitor_t mon1;
} FCA11_t;

// def @SPAS11 CAN Message (912)
#define SPAS11_IDE (0U)
#define SPAS11_DLC (7U)
#define SPAS11_CANID (0x390U)
// signal: @CR_Spas_StrAngCmd
#define SPAS11_CR_Spas_StrAngCmd_CovFactor (0.1)
// conversion value to CAN signal
#define SPAS11_CR_Spas_StrAngCmd_toS(x) ((int16_t)((x) / 0.1))
// conversion value from CAN signal
#define SPAS11_CR_Spas_StrAngCmd_fromS(x) ((x) * 0.1)

typedef struct
{

  uint8_t CF_Spas_Stat;                     //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Spas_TestMode;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  int16_t CR_Spas_StrAngCmd;                //  [-] Bits=16.  [ -3276.8, 3276.7 ]  Unit:''      Factor= 0.1   

  uint8_t CF_Spas_BeepAlarm;                //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Spas_Mode_Seq;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_AliveCnt;                 //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t CF_Spas_Chksum;                   //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t CF_Spas_PasVol;                   //      Bits=03.  [ 0     , 7      ]  Unit:''     
  FrameMonitor_t mon1;
} SPAS11_t;

// def @TCS12 CAN Message (915)
#define TCS12_IDE (0U)
#define TCS12_DLC (4U)
#define TCS12_CANID (0x393U)
// signal: @SA_COUNT
#define TCS12_SA_COUNT_CovFactor (2)
// conversion value to CAN signal
#define TCS12_SA_COUNT_toS(x) ((int32_t)((x) / 2 + 16384))
// conversion value from CAN signal
#define TCS12_SA_COUNT_fromS(x) ((x) * 2)

// signal: @SA_Z_COUNT
#define TCS12_SA_Z_COUNT_CovFactor (2)
// conversion value to CAN signal
#define TCS12_SA_Z_COUNT_toS(x) ((int16_t)((x) / 2 + 16384))
// conversion value from CAN signal
#define TCS12_SA_Z_COUNT_fromS(x) ((x) * 2)

typedef struct
{

  int32_t SA_COUNT;                         //      Bits=16.  [ -32768, 98302  ]  Unit:''      Offset= -32768    Factor= 2     

  int16_t SA_Z_COUNT;                       //      Bits=15.  [ -32768, 32766  ]  Unit:''      Offset= -32768    Factor= 2     

  uint8_t SA_Z_FLAG;                        //      Bits=01.  [ 0     , 1      ]  Unit:''     
  FrameMonitor_t mon1;
} TCS12_t;

// def @TCS13 CAN Message (916)
#define TCS13_IDE (0U)
#define TCS13_DLC (8U)
#define TCS13_CANID (0x394U)
// signal: @aBasis
#define TCS13_aBasis_CovFactor (0.01)
// conversion value to CAN signal
#define TCS13_aBasis_toS(x) ((int16_t)((x) / 0.01 + 1023))
// conversion value from CAN signal
#define TCS13_aBasis_fromS(x) ((x) * 0.01)

// signal: @TQI_ACC
#define TCS13_TQI_ACC_CovFactor (0.390625)
// conversion value to CAN signal
#define TCS13_TQI_ACC_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define TCS13_TQI_ACC_fromS(x) ((x) * 0.390625)

// signal: @ACCEL_REF_ACC
#define TCS13_ACCEL_REF_ACC_CovFactor (0.01)
// conversion value to CAN signal
#define TCS13_ACCEL_REF_ACC_toS(x) ((int16_t)((x) / 0.01 + 1023))
// conversion value from CAN signal
#define TCS13_ACCEL_REF_ACC_fromS(x) ((x) * 0.01)

typedef struct
{

  int16_t aBasis;                           //      Bits=11.  [ -10.23, 10.24  ]  Unit:'m/s^2' Offset= -10.23    Factor= 0.01  

  uint8_t BrakeLight;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t DCEnable;                         //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t AliveCounterTCS;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t ACCReqLim;                        //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t TQI_ACC;                          //      Bits=08.  [ 0     , 99.609375 ]  Unit:'%'     Factor= 0.390625

  int16_t ACCEL_REF_ACC;                    //      Bits=11.  [ -10.23, 10.24  ]  Unit:'m/s^2' Offset= -10.23    Factor= 0.01  

  uint8_t ACCEnable;                        //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t DriverOverride;                   //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t StandStill;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CheckSum_TCS3;                    //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t ACC_EQUIP;                        //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t PBRAKE_ACT;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ACC_REQ;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t DriverBraking;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_VSM_Coded;                     //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_VSM_Avail;                     //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_VSM_Handshake;                 //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_DriBkeStat;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_VSM_ConfSwi;                   //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t AEB_EQUIP;                        //      Bits=01.  [ 0     , 1      ]  Unit:''     
  FrameMonitor_t mon1;
} TCS13_t;

// def @SCC11 CAN Message (1056)
#define SCC11_IDE (0U)
#define SCC11_DLC (8U)
#define SCC11_CANID (0x420U)
// signal: @ACC_ObjLatPos
#define SCC11_ACC_ObjLatPos_CovFactor (0.1)
// conversion value to CAN signal
#define SCC11_ACC_ObjLatPos_toS(x) ((int16_t)((x) / 0.1 + 200))
// conversion value from CAN signal
#define SCC11_ACC_ObjLatPos_fromS(x) ((x) * 0.1)

// signal: @ACC_ObjDist
#define SCC11_ACC_ObjDist_CovFactor (0.1)
// conversion value to CAN signal
#define SCC11_ACC_ObjDist_toS(x) ((uint16_t)((x) / 0.1))
// conversion value from CAN signal
#define SCC11_ACC_ObjDist_fromS(x) ((x) * 0.1)

// signal: @ACC_ObjRelSpd
#define SCC11_ACC_ObjRelSpd_CovFactor (0.1)
// conversion value to CAN signal
#define SCC11_ACC_ObjRelSpd_toS(x) ((int16_t)((x) / 0.1 + 1700))
// conversion value from CAN signal
#define SCC11_ACC_ObjRelSpd_fromS(x) ((x) * 0.1)

typedef struct
{

  uint8_t MainMode_ACC;                     //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t SCCInfoDisplay;                   //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t AliveCounterACC;                  //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t VSetDis;                          //      Bits=08.  [ 0     , 255    ]  Unit:'km/h or MPH'

  uint8_t ObjValid;                         //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t DriverAlertDisplay;               //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t TauGapSet;                        //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t ACC_ObjStatus;                    //      Bits=02.  [ 0     , 3      ]  Unit:''     

  int16_t ACC_ObjLatPos;                    //      Bits=09.  [ -20   , 31.1   ]  Unit:'m'     Offset= -20       Factor= 0.1   

  uint16_t ACC_ObjDist;                     //      Bits=11.  [ 0     , 204.7  ]  Unit:'m'     Factor= 0.1   

  int16_t ACC_ObjRelSpd;                    //      Bits=12.  [ -170  , 239.5  ]  Unit:'m/s'   Offset= -170      Factor= 0.1   

  uint8_t Navi_SCC_Curve_Status;            //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t Navi_SCC_Curve_Act;               //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t Navi_SCC_Camera_Act;              //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t Navi_SCC_Camera_Status;           //      Bits=02.  [ 0     , 3      ]  Unit:''     
  FrameMonitor_t mon1;
} SCC11_t;

// def @SCC12 CAN Message (1057)
#define SCC12_IDE (0U)
#define SCC12_DLC (8U)
#define SCC12_CANID (0x421U)
// signal: @CR_VSM_DecCmd
#define SCC12_CR_VSM_DecCmd_CovFactor (0.01)
// conversion value to CAN signal
#define SCC12_CR_VSM_DecCmd_toS(x) ((uint8_t)((x) / 0.01))
// conversion value from CAN signal
#define SCC12_CR_VSM_DecCmd_fromS(x) ((x) * 0.01)

// signal: @aReqMax
#define SCC12_aReqMax_CovFactor (0.01)
// conversion value to CAN signal
#define SCC12_aReqMax_toS(x) ((int16_t)((x) / 0.01 + 1023))
// conversion value from CAN signal
#define SCC12_aReqMax_fromS(x) ((x) * 0.01)

// signal: @aReqMin
#define SCC12_aReqMin_CovFactor (0.01)
// conversion value to CAN signal
#define SCC12_aReqMin_toS(x) ((int16_t)((x) / 0.01 + 1023))
// conversion value from CAN signal
#define SCC12_aReqMin_fromS(x) ((x) * 0.01)

typedef struct
{

  uint8_t CF_VSM_Prefill;                   //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_VSM_DecCmdAct;                 //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_VSM_HBACmd;                    //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_VSM_Warn;                      //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_VSM_Stat;                      //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_VSM_BeltCmd;                   //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t ACCFailInfo;                      //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t ACCMode;                          //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t StopReq;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CR_VSM_DecCmd;                    //      Bits=08.  [ 0     , 2.55   ]  Unit:'g'     Factor= 0.01  

  int16_t aReqMax;                          //      Bits=11.  [ -10.23, 10.24  ]  Unit:'m/s^2' Offset= -10.23    Factor= 0.01  

  uint8_t TakeOverReq;                      //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t PreFill;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  int16_t aReqMin;                          //      Bits=11.  [ -10.23, 10.24  ]  Unit:'m/s^2' Offset= -10.23    Factor= 0.01  

  uint8_t CF_VSM_ConfMode;                  //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t AEB_Failinfo;                     //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t AEB_Status;                       //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t AEB_CmdAct;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t AEB_StopReq;                      //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CR_VSM_Alive;                     //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CR_VSM_ChkSum;                    //      Bits=04.  [ 0     , 15     ]  Unit:''     
  FrameMonitor_t mon1;
} SCC12_t;

// def @ESP11 CAN Message (1151)
#define ESP11_IDE (0U)
#define ESP11_DLC (6U)
#define ESP11_CANID (0x47FU)
// signal: @_4WD_CLU_LIM
#define ESP11__4WD_CLU_LIM_CovFactor (0.390625)
// conversion value to CAN signal
#define ESP11__4WD_CLU_LIM_toS(x) ((uint8_t)((x) / 0.390625))
// conversion value from CAN signal
#define ESP11__4WD_CLU_LIM_fromS(x) ((x) * 0.390625)

typedef struct
{

  uint8_t AVH_STAT;                         //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t LDM_STAT;                         //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t REQ_EPB_ACT;                      //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t REQ_EPB_STAT;                     //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ECD_ACT;                          //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t _4WD_LIM_REQ;                     //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t ROL_CNT_ESP;                      //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint16_t _4WD_TQC_LIM;                    //      Bits=16.  [ 0     , 65535  ]  Unit:'Nm'   

  uint8_t _4WD_CLU_LIM;                     //      Bits=08.  [ 0     , 99.609375 ]  Unit:'%'     Factor= 0.390625

  uint8_t _4WD_OPEN;                        //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t _4WD_LIM_MODE;                    //      Bits=01.  [ 0     , 1      ]  Unit:''     
  FrameMonitor_t mon1;
} ESP11_t;

// def @SPAS12 CAN Message (1268)
#define SPAS12_IDE (0U)
#define SPAS12_DLC (8U)
#define SPAS12_CANID (0x4F4U)
typedef struct
{

  uint8_t CF_Spas_HMI_Stat;                 //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t CF_Spas_Disp;                     //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_FIL_Ind;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_FIR_Ind;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_FOL_Ind;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_FOR_Ind;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_VolDown;                  //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_RIL_Ind;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_RIR_Ind;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_FLS_Alarm;                //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_ROL_Ind;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_ROR_Ind;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_FCS_Alarm;                //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_FI_Ind;                   //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_RI_Ind;                   //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t CF_Spas_FRS_Alarm;                //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_FR_Alarm;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_RR_Alarm;                 //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_BEEP_Alarm;               //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint8_t CF_Spas_StatAlarm;                //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t CF_Spas_RLS_Alarm;                //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_RCS_Alarm;                //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t CF_Spas_RRS_Alarm;                //      Bits=02.  [ 0     , 3      ]  Unit:''     
  FrameMonitor_t mon1;
} SPAS12_t;

// def @TCS15 CAN Message (1287)
#define TCS15_IDE (0U)
#define TCS15_DLC (4U)
#define TCS15_CANID (0x507U)
typedef struct
{

  uint8_t ABS_W_LAMP;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t TCS_OFF_LAMP;                     //      Bits=02.  [ 0     , 1      ]  Unit:''     

  uint8_t TCS_LAMP;                         //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t DBC_W_LAMP;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t DBC_F_LAMP;                       //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t ESC_Off_Step;                     //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t AVH_CLU;                          //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t AVH_I_LAMP;                       //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t EBD_W_LAMP;                       //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t AVH_ALARM;                        //      Bits=02.  [ 0     , 3      ]  Unit:''     

  uint8_t AVH_LAMP;                         //      Bits=03.  [ 0     , 7      ]  Unit:''     
  FrameMonitor_t mon1;
} TCS15_t;

// def @SCC13 CAN Message (1290)
#define SCC13_IDE (0U)
#define SCC13_DLC (8U)
#define SCC13_CANID (0x50AU)
typedef struct
{

  uint8_t SCCDrvModeRValue;                 //      Bits=03.  [ 0     , 7      ]  Unit:''     

  uint8_t SCC_Equip;                        //      Bits=01.  [ 0     , 1      ]  Unit:''     

  uint8_t AebDrvSetStatus;                  //      Bits=03.  [ 0     , 7      ]  Unit:''     
  FrameMonitor_t mon1;
} SCC13_t;

// def @CAL_SAS11 CAN Message (1984)
#define CAL_SAS11_IDE (0U)
#define CAL_SAS11_DLC (2U)
#define CAL_SAS11_CANID (0x7C0U)
typedef struct
{

  uint8_t CCW;                              //      Bits=04.  [ 0     , 15     ]  Unit:''     

  uint16_t SAS_CID;                         //      Bits=11.  [ 0     , 2047   ]  Unit:''     
  FrameMonitor_t mon1;
} CAL_SAS11_t;

uint32_t Unpack_ACU13_coderEx(ACU13_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_ACU13_coderEx(const ACU13_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_EMS18_coderEx(EMS18_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_EMS18_coderEx(const EMS18_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_DATC14_coderEx(DATC14_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_DATC14_coderEx(const DATC14_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_DATC12_coderEx(DATC12_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_DATC12_coderEx(const DATC12_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_DATC13_coderEx(DATC13_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_DATC13_coderEx(const DATC13_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_DATC11_coderEx(DATC11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_DATC11_coderEx(const DATC11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_CGW5_coderEx(CGW5_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_CGW5_coderEx(const CGW5_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_EMS_DCT11_coderEx(EMS_DCT11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_EMS_DCT11_coderEx(const EMS_DCT11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_EMS_DCT12_coderEx(EMS_DCT12_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_EMS_DCT12_coderEx(const EMS_DCT12_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_TCU11_coderEx(TCU11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_TCU11_coderEx(const TCU11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_TCU12_coderEx(TCU12_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_TCU12_coderEx(const TCU12_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_TCU13_coderEx(TCU13_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_TCU13_coderEx(const TCU13_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_TCS11_coderEx(TCS11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_TCS11_coderEx(const TCS11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_TCU_DCT13_coderEx(TCU_DCT13_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_TCU_DCT13_coderEx(const TCU_DCT13_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_VSM11_coderEx(VSM11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_VSM11_coderEx(const VSM11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_ESP12_coderEx(ESP12_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_ESP12_coderEx(const ESP12_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_WHL_SPD11_coderEx(WHL_SPD11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_WHL_SPD11_coderEx(const WHL_SPD11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_SCC14_coderEx(SCC14_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_SCC14_coderEx(const SCC14_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_ABS11_coderEx(ABS11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_ABS11_coderEx(const ABS11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_FCA11_coderEx(FCA11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_FCA11_coderEx(const FCA11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_SPAS11_coderEx(SPAS11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_SPAS11_coderEx(const SPAS11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_TCS12_coderEx(TCS12_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_TCS12_coderEx(const TCS12_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_TCS13_coderEx(TCS13_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_TCS13_coderEx(const TCS13_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_SCC11_coderEx(SCC11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_SCC11_coderEx(const SCC11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_SCC12_coderEx(SCC12_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_SCC12_coderEx(const SCC12_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_ESP11_coderEx(ESP11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_ESP11_coderEx(const ESP11_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_SPAS12_coderEx(SPAS12_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_SPAS12_coderEx(const SPAS12_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_TCS15_coderEx(TCS15_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_TCS15_coderEx(const TCS15_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_SCC13_coderEx(SCC13_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_SCC13_coderEx(const SCC13_t* _m, __CoderDbcCanFrame_t__* cframe);
uint32_t Unpack_CAL_SAS11_coderEx(CAL_SAS11_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_CAL_SAS11_coderEx(const CAL_SAS11_t* _m, __CoderDbcCanFrame_t__* cframe);

#ifdef __cplusplus
}
#endif

