// Coder Example Main Files 

#include "coderex.h"

// This include contains the prototypes of the functions that
// perform the main monitor checkin and notify other clients
// (e.g. DTC, logic behaviour etc)
// the *.c source code must be created by end-user or linkage error!
#include "fmon-coderex.h"

// --------------------------------------------------------------------------
uint32_t Unpack_ACU13_coderEx(ACU13_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CF_Acu_CshAct = (_d[0] & (0x01U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < ACU13_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @ACU13
  FMon_ACU13_coderEx(&_m->mon1);
  return ACU13_CANID;
}

uint32_t Pack_ACU13_coderEx(const ACU13_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < ACU13_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CF_Acu_CshAct & (0x01U));

  cframe->MsgId = ACU13_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return ACU13_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_EMS18_coderEx(EMS18_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CF_Ems_DC1NumPerMSV = (_d[0] & (0xFFU));
  _m->CF_Ems_DC2NumPerMSV = ((_d[2] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
  _m->CR_Ems_DutyCyc1MSV = (_d[3] & (0xFFU));
  _m->CR_Ems_DutyCyc2MSV = (_d[4] & (0xFFU));
  _m->CR_Ems_DutyCyc3MSV = (_d[5] & (0xFFU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < EMS18_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @EMS18
  FMon_EMS18_coderEx(&_m->mon1);
  return EMS18_CANID;
}

uint32_t Pack_EMS18_coderEx(const EMS18_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < EMS18_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CF_Ems_DC1NumPerMSV & (0xFFU));
  cframe->Data[1] |= (_m->CF_Ems_DC2NumPerMSV & (0xFFU));
  cframe->Data[2] |= ((_m->CF_Ems_DC2NumPerMSV >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->CR_Ems_DutyCyc1MSV & (0xFFU));
  cframe->Data[4] |= (_m->CR_Ems_DutyCyc2MSV & (0xFFU));
  cframe->Data[5] |= (_m->CR_Ems_DutyCyc3MSV & (0xFFU));

  cframe->MsgId = EMS18_CANID;
  cframe->DLC = 6;
  cframe->IDE = 0;
  return EMS18_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_DATC14_coderEx(DATC14_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CF_Datc_AqsLevelOut = (_d[0] & (0x0FU));
  _m->CF_Datc_DiagMode = ((_d[0] >> 6) & (0x03U));
  _m->CR_Datc_SelfDiagCode = ((_d[1] & (0xFFU))) - 1;
  _m->DATC_SyncDisp = (_d[2] & (0x0FU));
  _m->DATC_OffDisp = ((_d[2] >> 4) & (0x03U));
  _m->DATC_SmartVentDisp = ((_d[2] >> 6) & (0x03U));
  _m->DATC_SmartVentOnOffStatus = (_d[3] & (0x03U));
  _m->DATC_AutoDefogSysOff_Disp = ((_d[3] >> 2) & (0x03U));
  _m->DATC_ADSDisp = ((_d[3] >> 4) & (0x03U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < DATC14_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @DATC14
  FMon_DATC14_coderEx(&_m->mon1);
  return DATC14_CANID;
}

uint32_t Pack_DATC14_coderEx(const DATC14_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < DATC14_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CF_Datc_AqsLevelOut & (0x0FU)) | ((_m->CF_Datc_DiagMode & (0x03U)) << 6);
  cframe->Data[1] |= (_m->CR_Datc_SelfDiagCode & (0xFFU));
  cframe->Data[2] |= (_m->DATC_SyncDisp & (0x0FU)) | ((_m->DATC_OffDisp & (0x03U)) << 4) | ((_m->DATC_SmartVentDisp & (0x03U)) << 6);
  cframe->Data[3] |= (_m->DATC_SmartVentOnOffStatus & (0x03U)) | ((_m->DATC_AutoDefogSysOff_Disp & (0x03U)) << 2) | ((_m->DATC_ADSDisp & (0x03U)) << 4);

  cframe->MsgId = DATC14_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return DATC14_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_DATC12_coderEx(DATC12_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CR_Datc_DrTempDispC = ((_d[0] & (0xFFU))) + 28;
  _m->CR_Datc_DrTempDispF = ((_d[1] & (0xFFU))) + 56;
  _m->CR_Datc_PsTempDispC = ((_d[2] & (0xFFU))) + 28;
  _m->CR_Datc_PsTempDispF = ((_d[3] & (0xFFU))) + 56;
  _m->CR_Datc_RearDrTempDispC = ((_d[5] & (0xFFU))) + 28;
  _m->CR_Datc_RearDrTempDispF = ((_d[6] & (0xFFU))) + 58;
  _m->CF_Datc_CO2_Warning = (_d[7] & (0xFFU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < DATC12_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @DATC12
  FMon_DATC12_coderEx(&_m->mon1);
  return DATC12_CANID;
}

uint32_t Pack_DATC12_coderEx(const DATC12_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < DATC12_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CR_Datc_DrTempDispC & (0xFFU));
  cframe->Data[1] |= (_m->CR_Datc_DrTempDispF & (0xFFU));
  cframe->Data[2] |= (_m->CR_Datc_PsTempDispC & (0xFFU));
  cframe->Data[3] |= (_m->CR_Datc_PsTempDispF & (0xFFU));
  cframe->Data[5] |= (_m->CR_Datc_RearDrTempDispC & (0xFFU));
  cframe->Data[6] |= (_m->CR_Datc_RearDrTempDispF & (0xFFU));
  cframe->Data[7] |= (_m->CF_Datc_CO2_Warning & (0xFFU));

  cframe->MsgId = DATC12_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return DATC12_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_DATC13_coderEx(DATC13_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CF_Datc_TempDispUnit = (_d[0] & (0x03U));
  _m->CF_Datc_ModDisp = ((_d[0] >> 2) & (0x0FU));
  _m->CF_Datc_IonClean = ((_d[0] >> 6) & (0x03U));
  _m->CF_Datc_ChgReqDisp = (_d[1] & (0x03U));
  _m->CF_Datc_IntakeDisp = ((_d[1] >> 2) & (0x03U));
  _m->CF_Datc_AutoDisp = ((_d[1] >> 4) & (0x03U));
  _m->CF_Datc_FrDefLed = ((_d[1] >> 6) & (0x03U));
  _m->CF_Datc_AutoDefogBlink = (_d[2] & (0x03U));
  _m->CF_Datc_ClmScanDisp = ((_d[2] >> 2) & (0x03U));
  _m->CF_Datc_AqsDisp = ((_d[2] >> 4) & (0x03U));
  _m->CF_Datc_AcDisp = ((_d[2] >> 6) & (0x03U));
  _m->CF_Datc_OpSts = ((_d[3] >> 1) & (0x07U));
  _m->CF_Mtc_MaxAcDisp = ((_d[3] >> 4) & (0x03U));
  _m->CF_Datc_DualDisp = ((_d[3] >> 6) & (0x03U));
  _m->CF_Datc_PwrInf = (_d[4] & (0x0FU));
  _m->CF_Datc_RearManual = ((_d[4] >> 6) & (0x03U));
  _m->CF_Datc_RearAutoDisp = (_d[5] & (0x03U));
  _m->CF_Datc_RearOffDisp = ((_d[5] >> 2) & (0x03U));
  _m->CF_Datc_RearClimateScnDisp = ((_d[5] >> 4) & (0x03U));
  _m->CF_Datc_RearChgReqDisp = ((_d[5] >> 6) & (0x03U));
  _m->CF_Datc_RearModDisp = (_d[6] & (0x0FU));
  _m->CF_Datc_RearBlwDisp = ((_d[6] >> 4) & (0x0FU));
  _m->CF_Datc_PSModDisp = (_d[7] & (0x0FU));
  _m->CF_Datc_FrontBlwDisp = ((_d[7] >> 4) & (0x0FU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < DATC13_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @DATC13
  FMon_DATC13_coderEx(&_m->mon1);
  return DATC13_CANID;
}

uint32_t Pack_DATC13_coderEx(const DATC13_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < DATC13_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CF_Datc_TempDispUnit & (0x03U)) | ((_m->CF_Datc_ModDisp & (0x0FU)) << 2) | ((_m->CF_Datc_IonClean & (0x03U)) << 6);
  cframe->Data[1] |= (_m->CF_Datc_ChgReqDisp & (0x03U)) | ((_m->CF_Datc_IntakeDisp & (0x03U)) << 2) | ((_m->CF_Datc_AutoDisp & (0x03U)) << 4) | ((_m->CF_Datc_FrDefLed & (0x03U)) << 6);
  cframe->Data[2] |= (_m->CF_Datc_AutoDefogBlink & (0x03U)) | ((_m->CF_Datc_ClmScanDisp & (0x03U)) << 2) | ((_m->CF_Datc_AqsDisp & (0x03U)) << 4) | ((_m->CF_Datc_AcDisp & (0x03U)) << 6);
  cframe->Data[3] |= ((_m->CF_Datc_OpSts & (0x07U)) << 1) | ((_m->CF_Mtc_MaxAcDisp & (0x03U)) << 4) | ((_m->CF_Datc_DualDisp & (0x03U)) << 6);
  cframe->Data[4] |= (_m->CF_Datc_PwrInf & (0x0FU)) | ((_m->CF_Datc_RearManual & (0x03U)) << 6);
  cframe->Data[5] |= (_m->CF_Datc_RearAutoDisp & (0x03U)) | ((_m->CF_Datc_RearOffDisp & (0x03U)) << 2) | ((_m->CF_Datc_RearClimateScnDisp & (0x03U)) << 4) | ((_m->CF_Datc_RearChgReqDisp & (0x03U)) << 6);
  cframe->Data[6] |= (_m->CF_Datc_RearModDisp & (0x0FU)) | ((_m->CF_Datc_RearBlwDisp & (0x0FU)) << 4);
  cframe->Data[7] |= (_m->CF_Datc_PSModDisp & (0x0FU)) | ((_m->CF_Datc_FrontBlwDisp & (0x0FU)) << 4);

  cframe->MsgId = DATC13_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return DATC13_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_DATC11_coderEx(DATC11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CF_Datc_Type = (_d[0] & (0xFFU));
  _m->CF_Datc_VerMaj = (_d[1] & (0xFFU));
  _m->CF_Datc_VerMin = (_d[2] & (0xFFU));
  _m->CR_Datc_OutTempC = ((_d[3] & (0xFFU))) - 82;
  _m->CR_Datc_OutTempF = ((_d[4] & (0xFFU))) - 42;
  _m->CF_Datc_IncarTemp = ((_d[5] & (0xFFU))) - 80;
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < DATC11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @DATC11
  FMon_DATC11_coderEx(&_m->mon1);
  return DATC11_CANID;
}

uint32_t Pack_DATC11_coderEx(const DATC11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < DATC11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CF_Datc_Type & (0xFFU));
  cframe->Data[1] |= (_m->CF_Datc_VerMaj & (0xFFU));
  cframe->Data[2] |= (_m->CF_Datc_VerMin & (0xFFU));
  cframe->Data[3] |= (_m->CR_Datc_OutTempC & (0xFFU));
  cframe->Data[4] |= (_m->CR_Datc_OutTempF & (0xFFU));
  cframe->Data[5] |= (_m->CF_Datc_IncarTemp & (0xFFU));

  cframe->MsgId = DATC11_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return DATC11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_CGW5_coderEx(CGW5_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->C_StopLampLhOpenSts = (_d[0] & (0x01U));
  _m->C_StopLampRhOpenSts = ((_d[0] >> 1) & (0x01U));
  _m->C_HMSLOpenSts = ((_d[0] >> 2) & (0x01U));
  _m->C_HLampLowLhOpenSts = ((_d[0] >> 3) & (0x01U));
  _m->C_HLampLowRhOpenSts = ((_d[0] >> 4) & (0x01U));
  _m->C_HLampHighLhOpenSts = ((_d[0] >> 5) & (0x01U));
  _m->C_HLampHighRhOpenSts = ((_d[0] >> 6) & (0x01U));
  _m->C_DRLLampLhOpenSts = ((_d[0] >> 7) & (0x01U));
  _m->C_DRLLampRhOpenSts = (_d[1] & (0x01U));
  _m->C_RearFOGLhOpenSts = ((_d[1] >> 1) & (0x01U));
  _m->C_RearFOGRhOpenSts = ((_d[1] >> 2) & (0x01U));
  _m->C_FrontFOGLhOpenSts = ((_d[1] >> 3) & (0x01U));
  _m->C_FrontFOGRhOpenSts = ((_d[1] >> 4) & (0x01U));
  _m->C_RearEXTTailLhOpenSts = ((_d[1] >> 5) & (0x01U));
  _m->C_RearEXTTailRhOpenSts = ((_d[1] >> 6) & (0x01U));
  _m->C_FrontEXTTailLhOpenSts = ((_d[1] >> 7) & (0x01U));
  _m->C_FrontEXTTailRhOpenSts = (_d[2] & (0x01U));
  _m->C_RearTSIGLhOpenSts = ((_d[2] >> 1) & (0x01U));
  _m->C_RearTSIGRhOpenSts = ((_d[2] >> 2) & (0x01U));
  _m->C_FrontTSIGLhOpenSts = ((_d[2] >> 3) & (0x01U));
  _m->C_FrontTSIGRhOpenSts = ((_d[2] >> 4) & (0x01U));
  _m->C_SBendingLhOpenSts = ((_d[2] >> 5) & (0x01U));
  _m->C_SBendingRhOpenSts = ((_d[2] >> 6) & (0x01U));
  _m->C_LicensePlateLhOpenSts = ((_d[2] >> 7) & (0x01U));
  _m->C_LicensePlateRhOpenSts = (_d[3] & (0x01U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < CGW5_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @CGW5
  FMon_CGW5_coderEx(&_m->mon1);
  return CGW5_CANID;
}

uint32_t Pack_CGW5_coderEx(const CGW5_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < CGW5_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->C_StopLampLhOpenSts & (0x01U)) | ((_m->C_StopLampRhOpenSts & (0x01U)) << 1) | ((_m->C_HMSLOpenSts & (0x01U)) << 2) | ((_m->C_HLampLowLhOpenSts & (0x01U)) << 3) | ((_m->C_HLampLowRhOpenSts & (0x01U)) << 4) | ((_m->C_HLampHighLhOpenSts & (0x01U)) << 5) | ((_m->C_HLampHighRhOpenSts & (0x01U)) << 6) | ((_m->C_DRLLampLhOpenSts & (0x01U)) << 7);
  cframe->Data[1] |= (_m->C_DRLLampRhOpenSts & (0x01U)) | ((_m->C_RearFOGLhOpenSts & (0x01U)) << 1) | ((_m->C_RearFOGRhOpenSts & (0x01U)) << 2) | ((_m->C_FrontFOGLhOpenSts & (0x01U)) << 3) | ((_m->C_FrontFOGRhOpenSts & (0x01U)) << 4) | ((_m->C_RearEXTTailLhOpenSts & (0x01U)) << 5) | ((_m->C_RearEXTTailRhOpenSts & (0x01U)) << 6) | ((_m->C_FrontEXTTailLhOpenSts & (0x01U)) << 7);
  cframe->Data[2] |= (_m->C_FrontEXTTailRhOpenSts & (0x01U)) | ((_m->C_RearTSIGLhOpenSts & (0x01U)) << 1) | ((_m->C_RearTSIGRhOpenSts & (0x01U)) << 2) | ((_m->C_FrontTSIGLhOpenSts & (0x01U)) << 3) | ((_m->C_FrontTSIGRhOpenSts & (0x01U)) << 4) | ((_m->C_SBendingLhOpenSts & (0x01U)) << 5) | ((_m->C_SBendingRhOpenSts & (0x01U)) << 6) | ((_m->C_LicensePlateLhOpenSts & (0x01U)) << 7);
  cframe->Data[3] |= (_m->C_LicensePlateRhOpenSts & (0x01U));

  cframe->MsgId = CGW5_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return CGW5_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_EMS_DCT11_coderEx(EMS_DCT11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->PV_AV_CAN = (_d[0] & (0xFFU));
  _m->TQ_STND = (_d[1] & (0x3FU));
  _m->F_N_ENG = ((_d[1] >> 6) & (0x01U));
  _m->F_SUB_TQI = ((_d[1] >> 7) & (0x01U));
  _m->N = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->TQI_ACOR = (_d[4] & (0xFFU));
  _m->TQFR = (_d[5] & (0xFFU));
  _m->TQI = (_d[6] & (0xFFU));
  _m->CF_Ems_Alive = (_d[7] & (0x0FU));
  _m->CF_Ems_ChkSum = ((_d[7] >> 4) & (0x0FU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < EMS_DCT11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @EMS_DCT11
  FMon_EMS_DCT11_coderEx(&_m->mon1);
  return EMS_DCT11_CANID;
}

uint32_t Pack_EMS_DCT11_coderEx(const EMS_DCT11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < EMS_DCT11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->PV_AV_CAN & (0xFFU));
  cframe->Data[1] |= (_m->TQ_STND & (0x3FU)) | ((_m->F_N_ENG & (0x01U)) << 6) | ((_m->F_SUB_TQI & (0x01U)) << 7);
  cframe->Data[2] |= (_m->N & (0xFFU));
  cframe->Data[3] |= ((_m->N >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->TQI_ACOR & (0xFFU));
  cframe->Data[5] |= (_m->TQFR & (0xFFU));
  cframe->Data[6] |= (_m->TQI & (0xFFU));
  cframe->Data[7] |= (_m->CF_Ems_Alive & (0x0FU)) | ((_m->CF_Ems_ChkSum & (0x0FU)) << 4);

  cframe->MsgId = EMS_DCT11_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return EMS_DCT11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_EMS_DCT12_coderEx(EMS_DCT12_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CR_Ems_SoakTimeExt = (_d[0] & (0x3FU));
  _m->BRAKE_ACT = ((_d[0] >> 6) & (0x03U));
  _m->CF_Ems_EngOperStat = (_d[1] & (0xFFU));
  _m->CR_Ems_IndAirTemp = ((_d[2] & (0xFFU))) - 64;
  _m->CF_Ems_Alive2 = (_d[7] & (0x0FU));
  _m->CF_Ems_ChkSum2 = ((_d[7] >> 4) & (0x0FU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < EMS_DCT12_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @EMS_DCT12
  FMon_EMS_DCT12_coderEx(&_m->mon1);
  return EMS_DCT12_CANID;
}

uint32_t Pack_EMS_DCT12_coderEx(const EMS_DCT12_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < EMS_DCT12_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CR_Ems_SoakTimeExt & (0x3FU)) | ((_m->BRAKE_ACT & (0x03U)) << 6);
  cframe->Data[1] |= (_m->CF_Ems_EngOperStat & (0xFFU));
  cframe->Data[2] |= (_m->CR_Ems_IndAirTemp & (0xFFU));
  cframe->Data[7] |= (_m->CF_Ems_Alive2 & (0x0FU)) | ((_m->CF_Ems_ChkSum2 & (0x0FU)) << 4);

  cframe->MsgId = EMS_DCT12_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return EMS_DCT12_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_TCU11_coderEx(TCU11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->TQI_TCU_INC = (_d[0] & (0xFFU));
  _m->G_SEL_DISP = (_d[1] & (0x0FU));
  _m->F_TCU = ((_d[1] >> 4) & (0x03U));
  _m->TCU_TYPE = ((_d[1] >> 6) & (0x03U));
  _m->TCU_OBD = (_d[2] & (0x07U));
  _m->SWI_GS = ((_d[2] >> 3) & (0x01U));
  _m->GEAR_TYPE = ((_d[2] >> 4) & (0x0FU));
  _m->TQI_TCU = (_d[3] & (0xFFU));
  _m->TEMP_AT = ((_d[4] & (0xFFU))) - 40;
  _m->N_TC = ((_d[6] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
  _m->SWI_CC = (_d[7] & (0x03U));
  _m->CF_Tcu_Alive1 = ((_d[7] >> 2) & (0x03U));
  _m->CF_Tcu_ChkSum1 = ((_d[7] >> 4) & (0x0FU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < TCU11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @TCU11
  FMon_TCU11_coderEx(&_m->mon1);
  return TCU11_CANID;
}

uint32_t Pack_TCU11_coderEx(const TCU11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < TCU11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->TQI_TCU_INC & (0xFFU));
  cframe->Data[1] |= (_m->G_SEL_DISP & (0x0FU)) | ((_m->F_TCU & (0x03U)) << 4) | ((_m->TCU_TYPE & (0x03U)) << 6);
  cframe->Data[2] |= (_m->TCU_OBD & (0x07U)) | ((_m->SWI_GS & (0x01U)) << 3) | ((_m->GEAR_TYPE & (0x0FU)) << 4);
  cframe->Data[3] |= (_m->TQI_TCU & (0xFFU));
  cframe->Data[4] |= (_m->TEMP_AT & (0xFFU));
  cframe->Data[5] |= (_m->N_TC & (0xFFU));
  cframe->Data[6] |= ((_m->N_TC >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->SWI_CC & (0x03U)) | ((_m->CF_Tcu_Alive1 & (0x03U)) << 2) | ((_m->CF_Tcu_ChkSum1 & (0x0FU)) << 4);

  cframe->MsgId = TCU11_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return TCU11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_TCU12_coderEx(TCU12_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->ETL_TCU = (_d[0] & (0xFFU));
  _m->CUR_GR = (_d[1] & (0x0FU));
  _m->CF_Tcu_Alive = ((_d[1] >> 4) & (0x03U));
  _m->CF_Tcu_ChkSum = ((_d[1] >> 6) & (0x03U));
  _m->VS_TCU = (_d[2] & (0xFFU));
  _m->FUEL_CUT_TCU = ((_d[3] >> 4) & (0x01U));
  _m->INH_FUEL_CUT = ((_d[3] >> 5) & (0x01U));
  _m->IDLE_UP_TCU = ((_d[3] >> 6) & (0x01U));
  _m->N_INC_TCU = ((_d[3] >> 7) & (0x01U));
  _m->SPK_RTD_TCU = ((_d[4] & (0xFFU))) - 63;
  _m->N_TC_RAW = ((_d[6] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
  _m->VS_TCU_DECIMAL = (_d[7] & (0xFFU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < TCU12_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @TCU12
  FMon_TCU12_coderEx(&_m->mon1);
  return TCU12_CANID;
}

uint32_t Pack_TCU12_coderEx(const TCU12_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < TCU12_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ETL_TCU & (0xFFU));
  cframe->Data[1] |= (_m->CUR_GR & (0x0FU)) | ((_m->CF_Tcu_Alive & (0x03U)) << 4) | ((_m->CF_Tcu_ChkSum & (0x03U)) << 6);
  cframe->Data[2] |= (_m->VS_TCU & (0xFFU));
  cframe->Data[3] |= ((_m->FUEL_CUT_TCU & (0x01U)) << 4) | ((_m->INH_FUEL_CUT & (0x01U)) << 5) | ((_m->IDLE_UP_TCU & (0x01U)) << 6) | ((_m->N_INC_TCU & (0x01U)) << 7);
  cframe->Data[4] |= (_m->SPK_RTD_TCU & (0xFFU));
  cframe->Data[5] |= (_m->N_TC_RAW & (0xFFU));
  cframe->Data[6] |= ((_m->N_TC_RAW >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->VS_TCU_DECIMAL & (0xFFU));

  cframe->MsgId = TCU12_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return TCU12_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_TCU13_coderEx(TCU13_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->N_TGT_LUP = ((_d[0] & (0xFFU))) + 50;
  _m->SLOPE_TCU = ((_d[1] & (0x3FU))) - 32;
  _m->CF_Tcu_InhCda = ((_d[1] >> 6) & (0x01U));
  _m->CF_Tcu_IsgInhib = ((_d[1] >> 7) & (0x01U));
  _m->CF_Tcu_BkeOnReq = (_d[2] & (0x03U));
  _m->CF_Tcu_NCStat = ((_d[2] >> 2) & (0x03U));
  _m->CF_Tcu_TarGr = ((_d[2] >> 4) & (0x0FU));
  _m->CF_Tcu_ShfPatt = (_d[3] & (0x0FU));
  _m->CF_Tcu_InhVis = ((_d[3] >> 4) & (0x01U));
  _m->CF_Tcu_PRelReq = ((_d[3] >> 5) & (0x01U));
  _m->CF_Tcu_ITPhase = ((_d[3] >> 6) & (0x01U));
  _m->CF_Tcu_ActEcoRdy = ((_d[3] >> 7) & (0x01U));
  _m->CF_Tcu_TqGrdLim = (_d[4] & (0xFFU));
  _m->CR_Tcu_IsgTgtRPM = (_d[5] & (0xFFU));
  _m->CF_Tcu_SptRdy = (_d[6] & (0x01U));
  _m->CF_Tcu_SbwPInfo = (_d[7] & (0x01U));
  _m->CF_Tcu_Alive3 = ((_d[7] >> 2) & (0x03U));
  _m->CF_Tcu_ChkSum3 = ((_d[7] >> 4) & (0x0FU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < TCU13_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @TCU13
  FMon_TCU13_coderEx(&_m->mon1);
  return TCU13_CANID;
}

uint32_t Pack_TCU13_coderEx(const TCU13_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < TCU13_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->N_TGT_LUP & (0xFFU));
  cframe->Data[1] |= (_m->SLOPE_TCU & (0x3FU)) | ((_m->CF_Tcu_InhCda & (0x01U)) << 6) | ((_m->CF_Tcu_IsgInhib & (0x01U)) << 7);
  cframe->Data[2] |= (_m->CF_Tcu_BkeOnReq & (0x03U)) | ((_m->CF_Tcu_NCStat & (0x03U)) << 2) | ((_m->CF_Tcu_TarGr & (0x0FU)) << 4);
  cframe->Data[3] |= (_m->CF_Tcu_ShfPatt & (0x0FU)) | ((_m->CF_Tcu_InhVis & (0x01U)) << 4) | ((_m->CF_Tcu_PRelReq & (0x01U)) << 5) | ((_m->CF_Tcu_ITPhase & (0x01U)) << 6) | ((_m->CF_Tcu_ActEcoRdy & (0x01U)) << 7);
  cframe->Data[4] |= (_m->CF_Tcu_TqGrdLim & (0xFFU));
  cframe->Data[5] |= (_m->CR_Tcu_IsgTgtRPM & (0xFFU));
  cframe->Data[6] |= (_m->CF_Tcu_SptRdy & (0x01U));
  cframe->Data[7] |= (_m->CF_Tcu_SbwPInfo & (0x01U)) | ((_m->CF_Tcu_Alive3 & (0x03U)) << 2) | ((_m->CF_Tcu_ChkSum3 & (0x0FU)) << 4);

  cframe->MsgId = TCU13_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return TCU13_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_TCS11_coderEx(TCS11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->TCS_REQ = (_d[0] & (0x01U));
  _m->MSR_C_REQ = ((_d[0] >> 1) & (0x01U));
  _m->TCS_PAS = ((_d[0] >> 2) & (0x01U));
  _m->TCS_GSC = ((_d[0] >> 3) & (0x01U));
  _m->CF_Esc_LimoInfo = ((_d[0] >> 4) & (0x03U));
  _m->ABS_DIAG = ((_d[0] >> 6) & (0x01U));
  _m->ABS_DEF = ((_d[0] >> 7) & (0x01U));
  _m->TCS_DEF = (_d[1] & (0x01U));
  _m->TCS_CTL = ((_d[1] >> 1) & (0x01U));
  _m->ABS_ACT = ((_d[1] >> 2) & (0x01U));
  _m->EBD_DEF = ((_d[1] >> 3) & (0x01U));
  _m->ESP_PAS = ((_d[1] >> 4) & (0x01U));
  _m->ESP_DEF = ((_d[1] >> 5) & (0x01U));
  _m->ESP_CTL = ((_d[1] >> 6) & (0x01U));
  _m->TCS_MFRN = ((_d[1] >> 7) & (0x01U));
  _m->DBC_CTL = (_d[2] & (0x01U));
  _m->DBC_PAS = ((_d[2] >> 1) & (0x01U));
  _m->DBC_DEF = ((_d[2] >> 2) & (0x01U));
  _m->HAC_CTL = ((_d[2] >> 3) & (0x01U));
  _m->HAC_PAS = ((_d[2] >> 4) & (0x01U));
  _m->HAC_DEF = ((_d[2] >> 5) & (0x01U));
  _m->ESS_STAT = ((_d[2] >> 6) & (0x03U));
  _m->TQI_TCS = (_d[3] & (0xFFU));
  _m->TQI_MSR = (_d[4] & (0xFFU));
  _m->TQI_SLW_TCS = (_d[5] & (0xFFU));
  _m->CF_Esc_BrkCtl = (_d[6] & (0x01U));
  _m->BLA_CTL = ((_d[6] >> 1) & (0x03U));
  _m->AliveCounter_TCS1 = ((_d[6] >> 4) & (0x0FU));
  _m->CheckSum_TCS1 = (_d[7] & (0xFFU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < TCS11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @TCS11
  FMon_TCS11_coderEx(&_m->mon1);
  return TCS11_CANID;
}

uint32_t Pack_TCS11_coderEx(const TCS11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < TCS11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->TCS_REQ & (0x01U)) | ((_m->MSR_C_REQ & (0x01U)) << 1) | ((_m->TCS_PAS & (0x01U)) << 2) | ((_m->TCS_GSC & (0x01U)) << 3) | ((_m->CF_Esc_LimoInfo & (0x03U)) << 4) | ((_m->ABS_DIAG & (0x01U)) << 6) | ((_m->ABS_DEF & (0x01U)) << 7);
  cframe->Data[1] |= (_m->TCS_DEF & (0x01U)) | ((_m->TCS_CTL & (0x01U)) << 1) | ((_m->ABS_ACT & (0x01U)) << 2) | ((_m->EBD_DEF & (0x01U)) << 3) | ((_m->ESP_PAS & (0x01U)) << 4) | ((_m->ESP_DEF & (0x01U)) << 5) | ((_m->ESP_CTL & (0x01U)) << 6) | ((_m->TCS_MFRN & (0x01U)) << 7);
  cframe->Data[2] |= (_m->DBC_CTL & (0x01U)) | ((_m->DBC_PAS & (0x01U)) << 1) | ((_m->DBC_DEF & (0x01U)) << 2) | ((_m->HAC_CTL & (0x01U)) << 3) | ((_m->HAC_PAS & (0x01U)) << 4) | ((_m->HAC_DEF & (0x01U)) << 5) | ((_m->ESS_STAT & (0x03U)) << 6);
  cframe->Data[3] |= (_m->TQI_TCS & (0xFFU));
  cframe->Data[4] |= (_m->TQI_MSR & (0xFFU));
  cframe->Data[5] |= (_m->TQI_SLW_TCS & (0xFFU));
  cframe->Data[6] |= (_m->CF_Esc_BrkCtl & (0x01U)) | ((_m->BLA_CTL & (0x03U)) << 1) | ((_m->AliveCounter_TCS1 & (0x0FU)) << 4);
  cframe->Data[7] |= (_m->CheckSum_TCS1 & (0xFFU));

  cframe->MsgId = TCS11_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return TCS11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_TCU_DCT13_coderEx(TCU_DCT13_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->Clutch_Driving_Tq = (((_d[1] & (0x03U)) << 8) | (_d[0] & (0xFFU))) - 512;
  _m->Cluster_Engine_RPM = ((_d[2] & (0x7FU)) << 6) | ((_d[1] >> 2) & (0x3FU));
  _m->Cluster_Engine_RPM_Flag = ((_d[2] >> 7) & (0x01U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < TCU_DCT13_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @TCU_DCT13
  FMon_TCU_DCT13_coderEx(&_m->mon1);
  return TCU_DCT13_CANID;
}

uint32_t Pack_TCU_DCT13_coderEx(const TCU_DCT13_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < TCU_DCT13_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->Clutch_Driving_Tq & (0xFFU));
  cframe->Data[1] |= ((_m->Clutch_Driving_Tq >> 8) & (0x03U)) | ((_m->Cluster_Engine_RPM & (0x3FU)) << 2);
  cframe->Data[2] |= ((_m->Cluster_Engine_RPM >> 6) & (0x7FU)) | ((_m->Cluster_Engine_RPM_Flag & (0x01U)) << 7);

  cframe->MsgId = TCU_DCT13_CANID;
  cframe->DLC = 3;
  cframe->IDE = 0;
  return TCU_DCT13_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_VSM11_coderEx(VSM11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CR_Esc_StrTqReq = (((_d[1] & (0x0FU)) << 8) | (_d[0] & (0xFFU))) - 2048;
  _m->CF_Esc_Act = ((_d[1] >> 4) & (0x01U));
  _m->CF_Esc_CtrMode = ((_d[1] >> 5) & (0x07U));
  _m->CF_Esc_Def = (_d[2] & (0x01U));
  _m->CF_Esc_AliveCnt = ((_d[2] >> 1) & (0x0FU));
  _m->CF_Esc_Chksum = (_d[3] & (0xFFU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < VSM11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @VSM11
  FMon_VSM11_coderEx(&_m->mon1);
  return VSM11_CANID;
}

uint32_t Pack_VSM11_coderEx(const VSM11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < VSM11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CR_Esc_StrTqReq & (0xFFU));
  cframe->Data[1] |= ((_m->CR_Esc_StrTqReq >> 8) & (0x0FU)) | ((_m->CF_Esc_Act & (0x01U)) << 4) | ((_m->CF_Esc_CtrMode & (0x07U)) << 5);
  cframe->Data[2] |= (_m->CF_Esc_Def & (0x01U)) | ((_m->CF_Esc_AliveCnt & (0x0FU)) << 1);
  cframe->Data[3] |= (_m->CF_Esc_Chksum & (0xFFU));

  cframe->MsgId = VSM11_CANID;
  cframe->DLC = 4;
  cframe->IDE = 0;
  return VSM11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_ESP12_coderEx(ESP12_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->LAT_ACCEL = (((_d[1] & (0x07U)) << 8) | (_d[0] & (0xFFU))) - 1023;
  _m->LAT_ACCEL_STAT = ((_d[1] >> 3) & (0x01U));
  _m->LAT_ACCEL_DIAG = ((_d[1] >> 4) & (0x01U));
  _m->LONG_ACCEL = (((_d[2] & (0xFFU)) << 3) | ((_d[1] >> 5) & (0x07U))) - 1023;
  _m->LONG_ACCEL_STAT = (_d[3] & (0x01U));
  _m->LONG_ACCEL_DIAG = ((_d[3] >> 1) & (0x01U));
  _m->CYL_PRES = ((_d[4] & (0x3FU)) << 6) | ((_d[3] >> 2) & (0x3FU));
  _m->CYL_PRES_STAT = ((_d[4] >> 6) & (0x01U));
  _m->CYL_PRESS_DIAG = ((_d[4] >> 7) & (0x01U));
  _m->YAW_RATE = (((_d[6] & (0x1FU)) << 8) | (_d[5] & (0xFFU))) - 4095;
  _m->YAW_RATE_STAT = ((_d[6] >> 5) & (0x01U));
  _m->YAW_RATE_DIAG = ((_d[6] >> 6) & (0x01U));
  _m->ESP12_AliveCounter = (_d[7] & (0x0FU));
  _m->ESP12_Checksum = ((_d[7] >> 4) & (0x0FU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < ESP12_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @ESP12
  FMon_ESP12_coderEx(&_m->mon1);
  return ESP12_CANID;
}

uint32_t Pack_ESP12_coderEx(const ESP12_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < ESP12_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->LAT_ACCEL & (0xFFU));
  cframe->Data[1] |= ((_m->LAT_ACCEL >> 8) & (0x07U)) | ((_m->LAT_ACCEL_STAT & (0x01U)) << 3) | ((_m->LAT_ACCEL_DIAG & (0x01U)) << 4) | ((_m->LONG_ACCEL & (0x07U)) << 5);
  cframe->Data[2] |= ((_m->LONG_ACCEL >> 3) & (0xFFU));
  cframe->Data[3] |= (_m->LONG_ACCEL_STAT & (0x01U)) | ((_m->LONG_ACCEL_DIAG & (0x01U)) << 1) | ((_m->CYL_PRES & (0x3FU)) << 2);
  cframe->Data[4] |= ((_m->CYL_PRES >> 6) & (0x3FU)) | ((_m->CYL_PRES_STAT & (0x01U)) << 6) | ((_m->CYL_PRESS_DIAG & (0x01U)) << 7);
  cframe->Data[5] |= (_m->YAW_RATE & (0xFFU));
  cframe->Data[6] |= ((_m->YAW_RATE >> 8) & (0x1FU)) | ((_m->YAW_RATE_STAT & (0x01U)) << 5) | ((_m->YAW_RATE_DIAG & (0x01U)) << 6);
  cframe->Data[7] |= (_m->ESP12_AliveCounter & (0x0FU)) | ((_m->ESP12_Checksum & (0x0FU)) << 4);

  cframe->MsgId = ESP12_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return ESP12_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_WHL_SPD11_coderEx(WHL_SPD11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->WHL_SPD_FL = ((_d[1] & (0x3FU)) << 8) | (_d[0] & (0xFFU));
  _m->WHL_SPD_AliveCounter_LSB = ((_d[1] >> 6) & (0x03U));
  _m->WHL_SPD_FR = ((_d[3] & (0x3FU)) << 8) | (_d[2] & (0xFFU));
  _m->WHL_SPD_AliveCounter_MSB = ((_d[3] >> 6) & (0x03U));
  _m->WHL_SPD_RL = ((_d[5] & (0x3FU)) << 8) | (_d[4] & (0xFFU));
  _m->WHL_SPD_Checksum_LSB = ((_d[5] >> 6) & (0x03U));
  _m->WHL_SPD_RR = ((_d[7] & (0x3FU)) << 8) | (_d[6] & (0xFFU));
  _m->WHL_SPD_Checksum_MSB = ((_d[7] >> 6) & (0x03U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < WHL_SPD11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @WHL_SPD11
  FMon_WHL_SPD11_coderEx(&_m->mon1);
  return WHL_SPD11_CANID;
}

uint32_t Pack_WHL_SPD11_coderEx(const WHL_SPD11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < WHL_SPD11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->WHL_SPD_FL & (0xFFU));
  cframe->Data[1] |= ((_m->WHL_SPD_FL >> 8) & (0x3FU)) | ((_m->WHL_SPD_AliveCounter_LSB & (0x03U)) << 6);
  cframe->Data[2] |= (_m->WHL_SPD_FR & (0xFFU));
  cframe->Data[3] |= ((_m->WHL_SPD_FR >> 8) & (0x3FU)) | ((_m->WHL_SPD_AliveCounter_MSB & (0x03U)) << 6);
  cframe->Data[4] |= (_m->WHL_SPD_RL & (0xFFU));
  cframe->Data[5] |= ((_m->WHL_SPD_RL >> 8) & (0x3FU)) | ((_m->WHL_SPD_Checksum_LSB & (0x03U)) << 6);
  cframe->Data[6] |= (_m->WHL_SPD_RR & (0xFFU));
  cframe->Data[7] |= ((_m->WHL_SPD_RR >> 8) & (0x3FU)) | ((_m->WHL_SPD_Checksum_MSB & (0x03U)) << 6);

  cframe->MsgId = WHL_SPD11_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return WHL_SPD11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_SCC14_coderEx(SCC14_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->ComfortBandUpper = (_d[0] & (0x3FU));
  _m->ComfortBandLower = ((_d[1] & (0x0FU)) << 2) | ((_d[0] >> 6) & (0x03U));
  _m->JerkUpperLimit = ((_d[2] & (0x07U)) << 4) | ((_d[1] >> 4) & (0x0FU));
  _m->JerkLowerLimit = ((_d[3] & (0x03U)) << 5) | ((_d[2] >> 3) & (0x1FU));
  _m->SCCMode = (_d[4] & (0x07U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < SCC14_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @SCC14
  FMon_SCC14_coderEx(&_m->mon1);
  return SCC14_CANID;
}

uint32_t Pack_SCC14_coderEx(const SCC14_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < SCC14_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ComfortBandUpper & (0x3FU)) | ((_m->ComfortBandLower & (0x03U)) << 6);
  cframe->Data[1] |= ((_m->ComfortBandLower >> 2) & (0x0FU)) | ((_m->JerkUpperLimit & (0x0FU)) << 4);
  cframe->Data[2] |= ((_m->JerkUpperLimit >> 4) & (0x07U)) | ((_m->JerkLowerLimit & (0x1FU)) << 3);
  cframe->Data[3] |= ((_m->JerkLowerLimit >> 5) & (0x03U));
  cframe->Data[4] |= (_m->SCCMode & (0x07U));

  cframe->MsgId = SCC14_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return SCC14_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_ABS11_coderEx(ABS11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->ABS_DEF = (_d[0] & (0x01U));
  _m->EBD_DEF = ((_d[0] >> 1) & (0x01U));
  _m->ABS_ACT = ((_d[0] >> 2) & (0x01U));
  _m->ABS_W_LAMP = ((_d[0] >> 3) & (0x01U));
  _m->EBD_W_LAMP = ((_d[0] >> 4) & (0x01U));
  _m->ABS_DIAG = ((_d[0] >> 5) & (0x01U));
  _m->ESS_STAT = ((_d[0] >> 6) & (0x03U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < ABS11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @ABS11
  FMon_ABS11_coderEx(&_m->mon1);
  return ABS11_CANID;
}

uint32_t Pack_ABS11_coderEx(const ABS11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < ABS11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ABS_DEF & (0x01U)) | ((_m->EBD_DEF & (0x01U)) << 1) | ((_m->ABS_ACT & (0x01U)) << 2) | ((_m->ABS_W_LAMP & (0x01U)) << 3) | ((_m->EBD_W_LAMP & (0x01U)) << 4) | ((_m->ABS_DIAG & (0x01U)) << 5) | ((_m->ESS_STAT & (0x03U)) << 6);

  cframe->MsgId = ABS11_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return ABS11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_FCA11_coderEx(FCA11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CF_VSM_Prefill = (_d[0] & (0x01U));
  _m->CF_VSM_HBACmd = ((_d[0] >> 1) & (0x03U));
  _m->CF_VSM_Warn = ((_d[0] >> 3) & (0x03U));
  _m->CF_VSM_BeltCmd = ((_d[0] >> 5) & (0x07U));
  _m->CR_VSM_DecCmd = (_d[1] & (0xFFU));
  _m->FCA_Status = ((_d[2] >> 2) & (0x03U));
  _m->FCA_CmdAct = ((_d[2] >> 4) & (0x01U));
  _m->FCA_StopReq = ((_d[2] >> 5) & (0x01U));
  _m->FCA_DrvSetStatus = ((_d[3] & (0x01U)) << 2) | ((_d[2] >> 6) & (0x03U));
  _m->CF_VSM_DecCmdAct = ((_d[3] >> 7) & (0x01U));
  _m->FCA_Failinfo = (_d[4] & (0x07U));
  _m->CR_FCA_Alive = (_d[7] & (0x0FU));
  _m->CR_FCA_ChkSum = ((_d[7] >> 4) & (0x0FU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < FCA11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @FCA11
  FMon_FCA11_coderEx(&_m->mon1);
  return FCA11_CANID;
}

uint32_t Pack_FCA11_coderEx(const FCA11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < FCA11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CF_VSM_Prefill & (0x01U)) | ((_m->CF_VSM_HBACmd & (0x03U)) << 1) | ((_m->CF_VSM_Warn & (0x03U)) << 3) | ((_m->CF_VSM_BeltCmd & (0x07U)) << 5);
  cframe->Data[1] |= (_m->CR_VSM_DecCmd & (0xFFU));
  cframe->Data[2] |= ((_m->FCA_Status & (0x03U)) << 2) | ((_m->FCA_CmdAct & (0x01U)) << 4) | ((_m->FCA_StopReq & (0x01U)) << 5) | ((_m->FCA_DrvSetStatus & (0x03U)) << 6);
  cframe->Data[3] |= ((_m->FCA_DrvSetStatus >> 2) & (0x01U)) | ((_m->CF_VSM_DecCmdAct & (0x01U)) << 7);
  cframe->Data[4] |= (_m->FCA_Failinfo & (0x07U));
  cframe->Data[7] |= (_m->CR_FCA_Alive & (0x0FU)) | ((_m->CR_FCA_ChkSum & (0x0FU)) << 4);

  cframe->MsgId = FCA11_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return FCA11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_SPAS11_coderEx(SPAS11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CF_Spas_Stat = (_d[0] & (0x0FU));
  _m->CF_Spas_TestMode = ((_d[0] >> 4) & (0x03U));
  _m->CR_Spas_StrAngCmd = ((_d[2] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
  _m->CF_Spas_BeepAlarm = (_d[3] & (0x0FU));
  _m->CF_Spas_Mode_Seq = ((_d[3] >> 4) & (0x03U));
  _m->CF_Spas_AliveCnt = (_d[4] & (0xFFU));
  _m->CF_Spas_Chksum = (_d[5] & (0xFFU));
  _m->CF_Spas_PasVol = (_d[6] & (0x07U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < SPAS11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @SPAS11
  FMon_SPAS11_coderEx(&_m->mon1);
  return SPAS11_CANID;
}

uint32_t Pack_SPAS11_coderEx(const SPAS11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < SPAS11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CF_Spas_Stat & (0x0FU)) | ((_m->CF_Spas_TestMode & (0x03U)) << 4);
  cframe->Data[1] |= (_m->CR_Spas_StrAngCmd & (0xFFU));
  cframe->Data[2] |= ((_m->CR_Spas_StrAngCmd >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->CF_Spas_BeepAlarm & (0x0FU)) | ((_m->CF_Spas_Mode_Seq & (0x03U)) << 4);
  cframe->Data[4] |= (_m->CF_Spas_AliveCnt & (0xFFU));
  cframe->Data[5] |= (_m->CF_Spas_Chksum & (0xFFU));
  cframe->Data[6] |= (_m->CF_Spas_PasVol & (0x07U));

  cframe->MsgId = SPAS11_CANID;
  cframe->DLC = 7;
  cframe->IDE = 0;
  return SPAS11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_TCS12_coderEx(TCS12_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->SA_COUNT = (((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU))) - 16384;
  _m->SA_Z_COUNT = (((_d[3] & (0x7FU)) << 8) | (_d[2] & (0xFFU))) - 16384;
  _m->SA_Z_FLAG = ((_d[3] >> 7) & (0x01U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < TCS12_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @TCS12
  FMon_TCS12_coderEx(&_m->mon1);
  return TCS12_CANID;
}

uint32_t Pack_TCS12_coderEx(const TCS12_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < TCS12_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SA_COUNT & (0xFFU));
  cframe->Data[1] |= ((_m->SA_COUNT >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->SA_Z_COUNT & (0xFFU));
  cframe->Data[3] |= ((_m->SA_Z_COUNT >> 8) & (0x7FU)) | ((_m->SA_Z_FLAG & (0x01U)) << 7);

  cframe->MsgId = TCS12_CANID;
  cframe->DLC = 4;
  cframe->IDE = 0;
  return TCS12_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_TCS13_coderEx(TCS13_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->aBasis = (((_d[1] & (0x07U)) << 8) | (_d[0] & (0xFFU))) - 1023;
  _m->BrakeLight = ((_d[1] >> 3) & (0x01U));
  _m->DCEnable = ((_d[1] >> 4) & (0x01U));
  _m->AliveCounterTCS = ((_d[1] >> 5) & (0x07U));
  _m->ACCReqLim = ((_d[2] >> 6) & (0x03U));
  _m->TQI_ACC = (_d[3] & (0xFFU));
  _m->ACCEL_REF_ACC = (((_d[5] & (0x07U)) << 8) | (_d[4] & (0xFFU))) - 1023;
  _m->ACCEnable = ((_d[5] >> 3) & (0x03U));
  _m->DriverOverride = ((_d[5] >> 5) & (0x03U));
  _m->StandStill = ((_d[5] >> 7) & (0x01U));
  _m->CheckSum_TCS3 = (_d[6] & (0x0FU));
  _m->ACC_EQUIP = ((_d[6] >> 4) & (0x01U));
  _m->PBRAKE_ACT = ((_d[6] >> 5) & (0x01U));
  _m->ACC_REQ = ((_d[6] >> 6) & (0x01U));
  _m->DriverBraking = ((_d[6] >> 7) & (0x01U));
  _m->CF_VSM_Coded = (_d[7] & (0x01U));
  _m->CF_VSM_Avail = ((_d[7] >> 1) & (0x03U));
  _m->CF_VSM_Handshake = ((_d[7] >> 3) & (0x01U));
  _m->CF_DriBkeStat = ((_d[7] >> 4) & (0x01U));
  _m->CF_VSM_ConfSwi = ((_d[7] >> 5) & (0x03U));
  _m->AEB_EQUIP = ((_d[7] >> 7) & (0x01U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < TCS13_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @TCS13
  FMon_TCS13_coderEx(&_m->mon1);
  return TCS13_CANID;
}

uint32_t Pack_TCS13_coderEx(const TCS13_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < TCS13_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->aBasis & (0xFFU));
  cframe->Data[1] |= ((_m->aBasis >> 8) & (0x07U)) | ((_m->BrakeLight & (0x01U)) << 3) | ((_m->DCEnable & (0x01U)) << 4) | ((_m->AliveCounterTCS & (0x07U)) << 5);
  cframe->Data[2] |= ((_m->ACCReqLim & (0x03U)) << 6);
  cframe->Data[3] |= (_m->TQI_ACC & (0xFFU));
  cframe->Data[4] |= (_m->ACCEL_REF_ACC & (0xFFU));
  cframe->Data[5] |= ((_m->ACCEL_REF_ACC >> 8) & (0x07U)) | ((_m->ACCEnable & (0x03U)) << 3) | ((_m->DriverOverride & (0x03U)) << 5) | ((_m->StandStill & (0x01U)) << 7);
  cframe->Data[6] |= (_m->CheckSum_TCS3 & (0x0FU)) | ((_m->ACC_EQUIP & (0x01U)) << 4) | ((_m->PBRAKE_ACT & (0x01U)) << 5) | ((_m->ACC_REQ & (0x01U)) << 6) | ((_m->DriverBraking & (0x01U)) << 7);
  cframe->Data[7] |= (_m->CF_VSM_Coded & (0x01U)) | ((_m->CF_VSM_Avail & (0x03U)) << 1) | ((_m->CF_VSM_Handshake & (0x01U)) << 3) | ((_m->CF_DriBkeStat & (0x01U)) << 4) | ((_m->CF_VSM_ConfSwi & (0x03U)) << 5) | ((_m->AEB_EQUIP & (0x01U)) << 7);

  cframe->MsgId = TCS13_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return TCS13_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_SCC11_coderEx(SCC11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->MainMode_ACC = (_d[0] & (0x01U));
  _m->SCCInfoDisplay = ((_d[0] >> 1) & (0x07U));
  _m->AliveCounterACC = ((_d[0] >> 4) & (0x0FU));
  _m->VSetDis = (_d[1] & (0xFFU));
  _m->ObjValid = (_d[2] & (0x01U));
  _m->DriverAlertDisplay = ((_d[2] >> 1) & (0x03U));
  _m->TauGapSet = ((_d[2] >> 3) & (0x07U));
  _m->ACC_ObjStatus = ((_d[2] >> 6) & (0x03U));
  _m->ACC_ObjLatPos = (((_d[4] & (0x01U)) << 8) | (_d[3] & (0xFFU))) - 200;
  _m->ACC_ObjDist = ((_d[5] & (0x0FU)) << 7) | ((_d[4] >> 1) & (0x7FU));
  _m->ACC_ObjRelSpd = (((_d[6] & (0xFFU)) << 4) | ((_d[5] >> 4) & (0x0FU))) - 1700;
  _m->Navi_SCC_Curve_Status = (_d[7] & (0x03U));
  _m->Navi_SCC_Curve_Act = ((_d[7] >> 2) & (0x03U));
  _m->Navi_SCC_Camera_Act = ((_d[7] >> 4) & (0x03U));
  _m->Navi_SCC_Camera_Status = ((_d[7] >> 6) & (0x03U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < SCC11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @SCC11
  FMon_SCC11_coderEx(&_m->mon1);
  return SCC11_CANID;
}

uint32_t Pack_SCC11_coderEx(const SCC11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < SCC11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->MainMode_ACC & (0x01U)) | ((_m->SCCInfoDisplay & (0x07U)) << 1) | ((_m->AliveCounterACC & (0x0FU)) << 4);
  cframe->Data[1] |= (_m->VSetDis & (0xFFU));
  cframe->Data[2] |= (_m->ObjValid & (0x01U)) | ((_m->DriverAlertDisplay & (0x03U)) << 1) | ((_m->TauGapSet & (0x07U)) << 3) | ((_m->ACC_ObjStatus & (0x03U)) << 6);
  cframe->Data[3] |= (_m->ACC_ObjLatPos & (0xFFU));
  cframe->Data[4] |= ((_m->ACC_ObjLatPos >> 8) & (0x01U)) | ((_m->ACC_ObjDist & (0x7FU)) << 1);
  cframe->Data[5] |= ((_m->ACC_ObjDist >> 7) & (0x0FU)) | ((_m->ACC_ObjRelSpd & (0x0FU)) << 4);
  cframe->Data[6] |= ((_m->ACC_ObjRelSpd >> 4) & (0xFFU));
  cframe->Data[7] |= (_m->Navi_SCC_Curve_Status & (0x03U)) | ((_m->Navi_SCC_Curve_Act & (0x03U)) << 2) | ((_m->Navi_SCC_Camera_Act & (0x03U)) << 4) | ((_m->Navi_SCC_Camera_Status & (0x03U)) << 6);

  cframe->MsgId = SCC11_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return SCC11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_SCC12_coderEx(SCC12_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CF_VSM_Prefill = (_d[0] & (0x01U));
  _m->CF_VSM_DecCmdAct = ((_d[0] >> 1) & (0x01U));
  _m->CF_VSM_HBACmd = ((_d[0] >> 2) & (0x03U));
  _m->CF_VSM_Warn = ((_d[0] >> 4) & (0x03U));
  _m->CF_VSM_Stat = ((_d[0] >> 6) & (0x03U));
  _m->CF_VSM_BeltCmd = (_d[1] & (0x07U));
  _m->ACCFailInfo = ((_d[1] >> 3) & (0x03U));
  _m->ACCMode = ((_d[1] >> 5) & (0x03U));
  _m->StopReq = ((_d[1] >> 7) & (0x01U));
  _m->CR_VSM_DecCmd = (_d[2] & (0xFFU));
  _m->aReqMax = (((_d[4] & (0x07U)) << 8) | (_d[3] & (0xFFU))) - 1023;
  _m->TakeOverReq = ((_d[4] >> 3) & (0x01U));
  _m->PreFill = ((_d[4] >> 4) & (0x01U));
  _m->aReqMin = (((_d[5] & (0xFFU)) << 3) | ((_d[4] >> 5) & (0x07U))) - 1023;
  _m->CF_VSM_ConfMode = (_d[6] & (0x03U));
  _m->AEB_Failinfo = ((_d[6] >> 2) & (0x03U));
  _m->AEB_Status = ((_d[6] >> 4) & (0x03U));
  _m->AEB_CmdAct = ((_d[6] >> 6) & (0x01U));
  _m->AEB_StopReq = ((_d[6] >> 7) & (0x01U));
  _m->CR_VSM_Alive = (_d[7] & (0x0FU));
  _m->CR_VSM_ChkSum = ((_d[7] >> 4) & (0x0FU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < SCC12_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @SCC12
  FMon_SCC12_coderEx(&_m->mon1);
  return SCC12_CANID;
}

uint32_t Pack_SCC12_coderEx(const SCC12_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < SCC12_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CF_VSM_Prefill & (0x01U)) | ((_m->CF_VSM_DecCmdAct & (0x01U)) << 1) | ((_m->CF_VSM_HBACmd & (0x03U)) << 2) | ((_m->CF_VSM_Warn & (0x03U)) << 4) | ((_m->CF_VSM_Stat & (0x03U)) << 6);
  cframe->Data[1] |= (_m->CF_VSM_BeltCmd & (0x07U)) | ((_m->ACCFailInfo & (0x03U)) << 3) | ((_m->ACCMode & (0x03U)) << 5) | ((_m->StopReq & (0x01U)) << 7);
  cframe->Data[2] |= (_m->CR_VSM_DecCmd & (0xFFU));
  cframe->Data[3] |= (_m->aReqMax & (0xFFU));
  cframe->Data[4] |= ((_m->aReqMax >> 8) & (0x07U)) | ((_m->TakeOverReq & (0x01U)) << 3) | ((_m->PreFill & (0x01U)) << 4) | ((_m->aReqMin & (0x07U)) << 5);
  cframe->Data[5] |= ((_m->aReqMin >> 3) & (0xFFU));
  cframe->Data[6] |= (_m->CF_VSM_ConfMode & (0x03U)) | ((_m->AEB_Failinfo & (0x03U)) << 2) | ((_m->AEB_Status & (0x03U)) << 4) | ((_m->AEB_CmdAct & (0x01U)) << 6) | ((_m->AEB_StopReq & (0x01U)) << 7);
  cframe->Data[7] |= (_m->CR_VSM_Alive & (0x0FU)) | ((_m->CR_VSM_ChkSum & (0x0FU)) << 4);

  cframe->MsgId = SCC12_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return SCC12_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_ESP11_coderEx(ESP11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->AVH_STAT = (_d[0] & (0x03U));
  _m->LDM_STAT = ((_d[0] >> 2) & (0x01U));
  _m->REQ_EPB_ACT = ((_d[0] >> 3) & (0x03U));
  _m->REQ_EPB_STAT = ((_d[0] >> 5) & (0x01U));
  _m->ECD_ACT = ((_d[0] >> 6) & (0x01U));
  _m->_4WD_LIM_REQ = ((_d[0] >> 7) & (0x01U));
  _m->ROL_CNT_ESP = (_d[1] & (0xFFU));
  _m->_4WD_TQC_LIM = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->_4WD_CLU_LIM = (_d[4] & (0xFFU));
  _m->_4WD_OPEN = (_d[5] & (0x03U));
  _m->_4WD_LIM_MODE = ((_d[5] >> 2) & (0x01U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < ESP11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @ESP11
  FMon_ESP11_coderEx(&_m->mon1);
  return ESP11_CANID;
}

uint32_t Pack_ESP11_coderEx(const ESP11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < ESP11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->AVH_STAT & (0x03U)) | ((_m->LDM_STAT & (0x01U)) << 2) | ((_m->REQ_EPB_ACT & (0x03U)) << 3) | ((_m->REQ_EPB_STAT & (0x01U)) << 5) | ((_m->ECD_ACT & (0x01U)) << 6) | ((_m->_4WD_LIM_REQ & (0x01U)) << 7);
  cframe->Data[1] |= (_m->ROL_CNT_ESP & (0xFFU));
  cframe->Data[2] |= (_m->_4WD_TQC_LIM & (0xFFU));
  cframe->Data[3] |= ((_m->_4WD_TQC_LIM >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->_4WD_CLU_LIM & (0xFFU));
  cframe->Data[5] |= (_m->_4WD_OPEN & (0x03U)) | ((_m->_4WD_LIM_MODE & (0x01U)) << 2);

  cframe->MsgId = ESP11_CANID;
  cframe->DLC = 6;
  cframe->IDE = 0;
  return ESP11_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_SPAS12_coderEx(SPAS12_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CF_Spas_HMI_Stat = (_d[0] & (0xFFU));
  _m->CF_Spas_Disp = (_d[1] & (0x03U));
  _m->CF_Spas_FIL_Ind = ((_d[1] >> 2) & (0x07U));
  _m->CF_Spas_FIR_Ind = ((_d[1] >> 5) & (0x07U));
  _m->CF_Spas_FOL_Ind = (_d[2] & (0x07U));
  _m->CF_Spas_FOR_Ind = ((_d[2] >> 3) & (0x07U));
  _m->CF_Spas_VolDown = ((_d[2] >> 6) & (0x03U));
  _m->CF_Spas_RIL_Ind = (_d[3] & (0x07U));
  _m->CF_Spas_RIR_Ind = ((_d[3] >> 3) & (0x07U));
  _m->CF_Spas_FLS_Alarm = ((_d[3] >> 6) & (0x03U));
  _m->CF_Spas_ROL_Ind = (_d[4] & (0x07U));
  _m->CF_Spas_ROR_Ind = ((_d[4] >> 3) & (0x07U));
  _m->CF_Spas_FCS_Alarm = ((_d[4] >> 6) & (0x03U));
  _m->CF_Spas_FI_Ind = (_d[5] & (0x07U));
  _m->CF_Spas_RI_Ind = ((_d[5] >> 3) & (0x07U));
  _m->CF_Spas_FRS_Alarm = ((_d[5] >> 6) & (0x03U));
  _m->CF_Spas_FR_Alarm = (_d[6] & (0x03U));
  _m->CF_Spas_RR_Alarm = ((_d[6] >> 2) & (0x03U));
  _m->CF_Spas_BEEP_Alarm = ((_d[6] >> 4) & (0x0FU));
  _m->CF_Spas_StatAlarm = (_d[7] & (0x01U));
  _m->CF_Spas_RLS_Alarm = ((_d[7] >> 1) & (0x03U));
  _m->CF_Spas_RCS_Alarm = ((_d[7] >> 3) & (0x03U));
  _m->CF_Spas_RRS_Alarm = ((_d[7] >> 5) & (0x03U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < SPAS12_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @SPAS12
  FMon_SPAS12_coderEx(&_m->mon1);
  return SPAS12_CANID;
}

uint32_t Pack_SPAS12_coderEx(const SPAS12_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < SPAS12_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CF_Spas_HMI_Stat & (0xFFU));
  cframe->Data[1] |= (_m->CF_Spas_Disp & (0x03U)) | ((_m->CF_Spas_FIL_Ind & (0x07U)) << 2) | ((_m->CF_Spas_FIR_Ind & (0x07U)) << 5);
  cframe->Data[2] |= (_m->CF_Spas_FOL_Ind & (0x07U)) | ((_m->CF_Spas_FOR_Ind & (0x07U)) << 3) | ((_m->CF_Spas_VolDown & (0x03U)) << 6);
  cframe->Data[3] |= (_m->CF_Spas_RIL_Ind & (0x07U)) | ((_m->CF_Spas_RIR_Ind & (0x07U)) << 3) | ((_m->CF_Spas_FLS_Alarm & (0x03U)) << 6);
  cframe->Data[4] |= (_m->CF_Spas_ROL_Ind & (0x07U)) | ((_m->CF_Spas_ROR_Ind & (0x07U)) << 3) | ((_m->CF_Spas_FCS_Alarm & (0x03U)) << 6);
  cframe->Data[5] |= (_m->CF_Spas_FI_Ind & (0x07U)) | ((_m->CF_Spas_RI_Ind & (0x07U)) << 3) | ((_m->CF_Spas_FRS_Alarm & (0x03U)) << 6);
  cframe->Data[6] |= (_m->CF_Spas_FR_Alarm & (0x03U)) | ((_m->CF_Spas_RR_Alarm & (0x03U)) << 2) | ((_m->CF_Spas_BEEP_Alarm & (0x0FU)) << 4);
  cframe->Data[7] |= (_m->CF_Spas_StatAlarm & (0x01U)) | ((_m->CF_Spas_RLS_Alarm & (0x03U)) << 1) | ((_m->CF_Spas_RCS_Alarm & (0x03U)) << 3) | ((_m->CF_Spas_RRS_Alarm & (0x03U)) << 5);

  cframe->MsgId = SPAS12_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return SPAS12_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_TCS15_coderEx(TCS15_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->ABS_W_LAMP = (_d[0] & (0x01U));
  _m->TCS_OFF_LAMP = ((_d[0] >> 1) & (0x03U));
  _m->TCS_LAMP = ((_d[0] >> 3) & (0x03U));
  _m->DBC_W_LAMP = ((_d[0] >> 5) & (0x01U));
  _m->DBC_F_LAMP = ((_d[0] >> 6) & (0x03U));
  _m->ESC_Off_Step = (_d[1] & (0x03U));
  _m->AVH_CLU = (_d[2] & (0xFFU));
  _m->AVH_I_LAMP = (_d[3] & (0x03U));
  _m->EBD_W_LAMP = ((_d[3] >> 2) & (0x01U));
  _m->AVH_ALARM = ((_d[3] >> 3) & (0x03U));
  _m->AVH_LAMP = ((_d[3] >> 5) & (0x07U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < TCS15_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @TCS15
  FMon_TCS15_coderEx(&_m->mon1);
  return TCS15_CANID;
}

uint32_t Pack_TCS15_coderEx(const TCS15_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < TCS15_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ABS_W_LAMP & (0x01U)) | ((_m->TCS_OFF_LAMP & (0x03U)) << 1) | ((_m->TCS_LAMP & (0x03U)) << 3) | ((_m->DBC_W_LAMP & (0x01U)) << 5) | ((_m->DBC_F_LAMP & (0x03U)) << 6);
  cframe->Data[1] |= (_m->ESC_Off_Step & (0x03U));
  cframe->Data[2] |= (_m->AVH_CLU & (0xFFU));
  cframe->Data[3] |= (_m->AVH_I_LAMP & (0x03U)) | ((_m->EBD_W_LAMP & (0x01U)) << 2) | ((_m->AVH_ALARM & (0x03U)) << 3) | ((_m->AVH_LAMP & (0x07U)) << 5);

  cframe->MsgId = TCS15_CANID;
  cframe->DLC = 4;
  cframe->IDE = 0;
  return TCS15_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_SCC13_coderEx(SCC13_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->SCCDrvModeRValue = (_d[0] & (0x07U));
  _m->SCC_Equip = ((_d[0] >> 3) & (0x01U));
  _m->AebDrvSetStatus = ((_d[0] >> 4) & (0x07U));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < SCC13_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @SCC13
  FMon_SCC13_coderEx(&_m->mon1);
  return SCC13_CANID;
}

uint32_t Pack_SCC13_coderEx(const SCC13_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < SCC13_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SCCDrvModeRValue & (0x07U)) | ((_m->SCC_Equip & (0x01U)) << 3) | ((_m->AebDrvSetStatus & (0x07U)) << 4);

  cframe->MsgId = SCC13_CANID;
  cframe->DLC = 8;
  cframe->IDE = 0;
  return SCC13_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_CAL_SAS11_coderEx(CAL_SAS11_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  _m->CCW = (_d[0] & (0x0FU));
  _m->SAS_CID = ((_d[1] & (0x7FU)) << 4) | ((_d[0] >> 4) & (0x0FU));
  // check DLC correctness
  _m->mon1.dlc_error = (dlc_ < CAL_SAS11_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  // Calling monitor function for @CAL_SAS11
  FMon_CAL_SAS11_coderEx(&_m->mon1);
  return CAL_SAS11_CANID;
}

uint32_t Pack_CAL_SAS11_coderEx(const CAL_SAS11_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; i < CAL_SAS11_DLC; cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CCW & (0x0FU)) | ((_m->SAS_CID & (0x0FU)) << 4);
  cframe->Data[1] |= ((_m->SAS_CID >> 4) & (0x7FU));

  cframe->MsgId = CAL_SAS11_CANID;
  cframe->DLC = 2;
  cframe->IDE = 0;
  return CAL_SAS11_CANID;
}

