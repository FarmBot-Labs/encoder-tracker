//###########################################################################
// App.h
// Top level application class
//
// $Copyright: Copyright (C) LDO Systems
//###########################################################################
#ifndef __APP_H__
#define __APP_H_
#include "AppHeaders.h"
#include "Encoder.h"
#include "Nvic.h"
#include "ExtInterrupt.h"
#include "Spi.h"
#include "Gpi.h"
#include "Gpo.h"


class App
{
private:
	static const uint16_t num_encoders = 4;
	static const uint8_t cmd_mask = 0x0F;
	static const uint8_t enc_offset = 4;
	static const uint8_t read_cmd = 0x0F;
	static const uint8_t reset_cmd = 0x00;

	enum EncoderIndex
	{
		_X1 = 0,
		_X2 = 1,
		_Y = 2,
		_Z = 3,
	};

	ExtInterrupt exti;
	Spi spi;
	Encoder encoderList[num_encoders];
	int32_t encoderVals[num_encoders];
	uint16_t oldEncoderCounts[num_encoders];

	void ConfigEncoder();
	void ConfigSpi();
	void ConfigExtInt();
	void SendEncoderVals(uint8_t header);
	void ClearEncoderVals(uint8_t header);

public:
	App();
	void Initialize();
	void Execute();
	void ServeSpi();
	void ExtIntClear();
};


#endif //__APP_H__
