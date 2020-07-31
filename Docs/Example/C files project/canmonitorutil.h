// Generated at @Tuesday, 28 July, 2020 20:29:13. Ver: 0.1
// This file has the common name. When a few DBC source code drivers are used you need to
// provide only one copy of it.
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum DbcCanCrcMethods {
  kCRCUndefined = 0,
  kSAEJ1850 = 1,
  kXOR8 = 2,
  kXOR4 = 3
};

typedef struct {
  // @last_cycle keeps tick-value when last frame was received
  uint32_t last_cycle;

  // @timeout_cycle keeps maximum timeout for frame
  uint32_t timeout_cycle;

  // @frame_cnt keeps count of all the received frames
  uint32_t frame_cnt;

  // this expected @RC value
  uint8_t roll_expect;

  // setting up @roll_error bit indicates roll counting fail. Bit is not clearing automatically!
  uint32_t roll_error : 1;

  // setting up @checksum_error bit indicates checksum checking failure. Bit is not clearing automatically!
  uint32_t checksum_error : 1;

  // setting up @cycle_error bit indicates that time was overrunned. Bit is not clearing automatically!
  uint32_t cycle_error : 1;

  // setting up @dlc_error bit indicates that the actual DLC of CAN frame is not equal to defined by CAN matrix!
  uint32_t dlc_error : 1;

} FrameMonitor_t;

/* ----------------------------------------------------------------------------- */
// If your CAN matrix has the messages that must be controlled with @Checksum calculation
// then the calculation function must be presented in your code :

uint8_t GetCrcValueForArray(const uint8_t* d, uint8_t len, uint32_t method, uint8_t op);

// @d - array for CRC calculation
// @len - amount of bytes for calculation
// @method - CRC algorythm. It can be enum value or define and must be defined outside this scope
// @op - not defined yet

/* ----------------------------------------------------------------------------- */
// this function will be called when unpacking is performing. Value will be saved
// in @last_cycle variable
uint32_t GetSystemTick(void);


#ifdef __cplusplus
}
#endif
