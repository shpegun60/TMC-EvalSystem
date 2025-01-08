/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#include "tmc_app.h"
#include "boards/Board.h"
#include "hal/derivative.h"
#include "tmc/IdDetection.h"
#include "tmc/TMCL.h"
#include "tmc/VitalSignsMonitor.h"
#include "tmc/BoardAssignment.h"
#include "tmc/RAMDebug.h"
#include "hal/tmc_port.h"

const char *VersionString = MODULE_ID "V310"; // module id and version of the firmware shown in the TMCL-IDE

EvalboardsTypeDef Evalboards;

// This struct gets placed at a specific address by the linker
struct BootloaderConfig BLConfig;

// => TMC-API wrapper
void tmc6100_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength)
{
	DRIVER_CS_LOW();
	DRIVER_SPI_READ_WRITE(data, data, dataLength);
	DRIVER_CS_HIGH();
	(void)icID;
}
// => TMC-API wrapper


// => SPI wrapper
void tmc4671_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength)
{
	CTRL_CS_LOW();
	CTRL_SPI_READ_WRITE(data, data, dataLength);
	CTRL_CS_HIGH();
	(void)icID;
}
// <= SPI wrapper

uint8_t tx_data[5];
uint8_t tx_data1[5] = {0};
uint8_t rx_data[5];
uint64_t value = 0x8100000000;
uint32_t readed = 0;


/* Call all standard initialization routines. */
void tmcl_app_init(void)
{
	tx_data[0] = (value >> 32) & 0xFF;
	tx_data[1] = (value >> 24) & 0xFF;
	tx_data[2] = (value >> 16) & 0xFF;
	tx_data[3] = (value >>  8) & 0xFF;
	tx_data[4] = (value >>  0) & 0xFF;

	DRIVER_CS_HIGH();
	CTRL_CS_HIGH();
	tmcl_init();                 // Initialize TMCL communication

	tmcdriver_init();            // Initialize dummy driver board --> preset EvalBoards.ch2
	tmcmotioncontroller_init();  // Initialize dummy motion controller board  --> preset EvalBoards.ch1

	VitalSignsMonitor.busy = 1;  // Put state to busy
	Evalboards.driverEnable = DRIVER_ENABLE;
	Evalboards.ch1.id = 0;       // preset id for driver board to 0 --> error/not found
	Evalboards.ch2.id = 0;       // preset id for driver board to 0 --> error/not found

	IdAssignmentTypeDef ids = { 0 };
	IDDetection_initialScan(&ids);  // start initial board detection
	IDDetection_initialScan(&ids);  // start second time, first time not 100% reliable, not sure why - too fast after startup?
	if(!ids.ch1.id && !ids.ch2.id) {
		tmcl_boot();
	}
	Board_assign(&ids);             // assign boards with detected id
	VitalSignsMonitor.busy 	= 0;    // not busy any more!
}

//#include "tmc/ic/TMC4671/TMC4671.h"
#include "tmc/ic/TMC6100/TMC6100.h"
/* main function */
void tmcl_app_loop(void)
{
	// Check all parameters and life signs and mark errors
	vitalsignsmonitor_checkVitalSigns();

	// handle RAMDebug
	debug_process();

	// Perodic jobs of Motion controller/Driver boards
	Evalboards.ch1.periodicJob(HAL_GetTick());
	Evalboards.ch2.periodicJob(HAL_GetTick());

	// Process TMCL communication
	tmcl_process();

//	CTRL_CS_LOW();
//	HAL_SPI_Transmit(&hspi1, tx_data, 5, 1000);
//	CTRL_CS_HIGH();

//	tmc4671_writeRegister(0, TMC4671_CHIPINFO_ADDR, 1);
//	readed = tmc4671_readRegister(0, TMC4671_CHIPINFO_DATA);

//	tmc6100_writeRegister(0, TMC6100_GCONF, 0x00000010);
//	readed = tmc6100_readRegister(0, TMC6100_GSTAT);

//	//HAL_Delay(1);
//	CTRL_CS_LOW();
//	HAL_SPI_TransmitReceive(&hspi1, tx_data1, rx_data, 5, 1000);
//	CTRL_CS_HIGH();
}
