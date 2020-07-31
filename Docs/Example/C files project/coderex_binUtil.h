// Coder Example Main Files 

#pragma once


#ifdef __cplusplus
extern "C" {
#endif

#include "coderex.h"

// @dbccodeconf.h file should be placed in inc folder. If the user wants
// to allocate big DBC struct inside the driver - appropriate define (__DEF_xxxxx__)
// should be placed in this file
#include "dbccodeconf.h"

typedef struct
{
  ACU13_t ACU13;                   // TX [ACU].     RX [CUBIS IBOX ODS ].
  EMS18_t EMS18;                   // TX [EMS].     RX [DI_BOX ].
  DATC14_t DATC14;                 // TX [DATC].    RX [CLU ].
  TCU_DCT13_t TCU_DCT13;           // TX [TCU].     RX [CLU ESC ].
  VSM11_t VSM11;                   // TX [ESC].     RX [LDWS_LKAS MDPS ].
} coderEx_rx_t;

typedef struct
{
  ACU13_t ACU13;                   // TX [ACU].     RX [CUBIS IBOX ODS ].
  EMS18_t EMS18;                   // TX [EMS].     RX [DI_BOX ].
  DATC14_t DATC14;                 // TX [DATC].    RX [CLU ].
  TCU11_t TCU11;                   // TX [TCU].     RX [_4WD AAF AFLS AVM BCM CGW CLU CUBIS ECS EMS EPB ESC IAP IBOX LCA LDWS_LKAS LVR MDPS PGS SCC SMK SNV SPAS TPMS ].
  TCU12_t TCU12;                   // TX [TCU].     RX [_4WD BCM CLU DATC EMS ESC IBOX LCA LVR PGS SCC SMK SNV TPMS ].
} coderEx_tx_t;


uint32_t coderEx_Receive(coderEx_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_);


// define @__DEF_CODEREX__ in the @dbccodeconf.h file for allocation in utility source code.
#ifdef __DEF_CODEREX__

extern coderEx_rx_t coderEx_rx;

extern coderEx_tx_t coderEx_tx;

#endif


#ifdef __cplusplus
}
#endif

