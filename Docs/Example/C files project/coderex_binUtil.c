// Coder Example Main Files 

#include "coderex_binUtil.h"

#ifdef __DEF_CODEREX__

coderEx_rx_t coderEx_rx;

coderEx_tx_t coderEx_tx;

#endif

uint32_t coderEx_Receive(coderEx_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if (_id >= 0x10U && _id < 0x40U) {
  if (_id == 0x10U) {
   recid = Unpack_ACU13_coderEx(&(_m->ACU13), _d, dlc_);
  } else if (_id == 0x30U) {
   recid = Unpack_EMS18_coderEx(&(_m->EMS18), _d, dlc_);
  }
 } else {
  if (_id == 0x40U) {
   recid = Unpack_DATC14_coderEx(&(_m->DATC14), _d, dlc_);
  } else {
   if (_id == 0x162U) {
    recid = Unpack_TCU_DCT13_coderEx(&(_m->TCU_DCT13), _d, dlc_);
   } else if (_id == 0x164U) {
    recid = Unpack_VSM11_coderEx(&(_m->VSM11), _d, dlc_);
   }
  }
 }

 return recid;
}

