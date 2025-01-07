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

const char *VersionString = MODULE_ID "V310"; // module id and version of the firmware shown in the TMCL-IDE

EvalboardsTypeDef Evalboards;

// This struct gets placed at a specific address by the linker
struct BootloaderConfig BLConfig;


/* Call all standard initialization routines. */
void tmcl_app_init(void)
{
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
}
