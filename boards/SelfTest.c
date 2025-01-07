/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "tmc/IdDetection.h"
#include "SelfTest.h"
#include "Board.h"

static void deInit();
static uint32_t selfTest(uint8_t type, uint8_t motor, int32_t *value);
static void periodicJob(uint32_t tick);

void SelfTest_init()
{
	VitalSignsMonitor.debugMode = 1;

	Evalboards.ch1.userFunction  = selfTest;
	Evalboards.ch1.deInit        = deInit;
	Evalboards.ch1.periodicJob   = periodicJob;
}

static void deInit()
{
	IDDetection_init();
	VitalSignsMonitor.debugMode = 0;
}

static uint32_t selfTest(uint8_t type, uint8_t motor, int32_t *value)
{
	int32_t result = 0xFFFFFFFF;
	uint32_t errors = TMC_ERROR_NONE;


	// 1 40 1 0 0 10 C9 45 60
	// 1 40 2 0 0 0 0 0 43
	// 1 40 3 0 0 0 0 0 44
	// 1 40 5 0 0 0 0 0 45
	// 1 40 6 0 0 0 0 0 46

	// 1 40 1 0 0 10 C9 45 60 1 40 2 0 0 0 0 0 43 1 40 3 0 0 0 0 0 44

	switch(type)
	{
	case SELF_TEST_LEAVE:
		deInit();
		*value = 32168;
		break;
	case SELF_TEST_A_OUT_B_IN:
	case SELF_TEST_A_IN_B_OUT:
		*value = result;
		break;
	case SELF_TEST_READ_AN:
		*value = motor;

		switch(motor)
		{
		case 0:
			*value = (uint32_t) (((10)/4095.0)*5.016*10);
			break;
		case 1:
			*value = (uint32_t) (((20)/4095.0)*5.016*10);
			break;
		case 2:
			*value = (uint32_t) (((30)/4095.0)*5.016*10);
			break;
		case 3:
			*value = VitalSignsMonitor.VM;
			break;
		default:
			errors |= TMC_ERROR_FUNCTION;
			break;
		}
		break;
	case SELF_TEST_SET_AN:
		*value = motor;

		switch(motor)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			errors |= TMC_ERROR_FUNCTION;
			break;
		}
		break;
	case SELF_TEST_SET_AN_2:
		*value = motor;

		switch(motor)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			errors |= TMC_ERROR_FUNCTION;
			break;
		}
		break;
	default:
		errors |= TMC_ERROR_TYPE;
		break;
	}
	return errors;
}

static void periodicJob(uint32_t tick)
{
	static uint32_t lastTick = 0;

	if((tick - lastTick) >= 500)
	{
		//HAL.LEDs->error.toggle();
		lastTick = tick;
	}
}
