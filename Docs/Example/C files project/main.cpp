// TestDbcUsage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "coderex_binUtil.h"

CanRxFrame txframe;

void TestDBCDriver()
{
	CanRxFrame rxtestframe;

	rxtestframe.MsgId = VSM11_CANID;
	rxtestframe.DLC = VSM11_DLC;
	rxtestframe.IDE = VSM11_IDE;

	rxtestframe.Data[0] = 0xB8;
	rxtestframe.Data[1] = 0x5B;

	// Frame from CAN bus is passing through CAN parser via *_Receive function
	// Proper ID or 0 will be returned
	auto id = coderEx_Receive(&coderEx_rx, rxtestframe.Data, rxtestframe.MsgId, rxtestframe.DLC);

	if (id == VSM11_CANID)
	{
		// coderEx_rx.VSM11 was unpacked
		std::cout << "Abs11 frame received : " << std::endl;
		// to get meaningful value fromS macro must be applied
		std::cout << "CR_Esc_StrTqRe =" << double(VSM11_CR_Esc_StrTqReq_fromS(coderEx_rx.VSM11.CR_Esc_StrTqReq)) << std::endl;
		std::cout << "CF_Esc_Act =" << int(coderEx_rx.VSM11.CF_Esc_Act) << std::endl;
		std::cout << "CF_Esc_CtrMode = " << int(coderEx_rx.VSM11.CF_Esc_CtrMode) << std::endl;
	}

	// Make packing back
	coderEx_rx.VSM11.CR_Esc_StrTqReq = VSM11_CR_Esc_StrTqReq_toS(-10.0);
	coderEx_rx.VSM11.CF_Esc_Act = 0;
	coderEx_rx.VSM11.CF_Esc_AliveCnt = 10;
	coderEx_rx.VSM11.CF_Esc_Chksum = 0xE1;

	// Pack signal to CAN struct
	Pack_VSM11_coderEx(&coderEx_rx.VSM11, &txframe);

	// tx frame now ready to be sent
	// CANNodeSendFrame(&txframe);
	std::cout << std::endl;
	std::cout << "Pack >> ";
	std::cout << "MsgId : " << int(txframe.MsgId) << std::endl;
	std::cout << "DLC : " << int(txframe.DLC) << std::endl;

	for (int32_t i = 0; i < txframe.DLC && i < 8; i++)
	{
		std::cout << "Data [" << int(i) << "] = " << int(txframe.Data[i]) << std::endl;
	}
}

int main()
{
	TestDBCDriver();
}
