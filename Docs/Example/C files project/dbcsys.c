#include "canmonitorutil.h"


uint32_t GetSystemTick()
{
	// This function must return global system tick (tick width is up to user)
	return 0;
}

// For CRC calculation case

uint8_t GetCrcValueForArray(const uint8_t* d, uint8_t len, uint32_t method, uint8_t op)
{
	uint8_t ret = 0xff;

	switch (method)
	{
	case(kCRCUndefined):
		ret = 10;
		break;
	default:
		break;
	}

	return ret;
}

