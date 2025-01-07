/*******************************************************************************
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

/*
 *  Calling IDDetection_detect(IdAssignmentTypeDef *result) will start the ID detection process.
 *  The function returns the ID Results through the IdAssignmentTypeDef struct result points to.
 *  The detection will be done by monoflop pulse duration measurement or via EEPROM readout.
 *  While this process is still ongoing the function will return ID_STATE_WAIT_HIGH. Once the
 *  ID detection of both channels has been finished, ID_STATE_DONE will be returned.
 *
 *  Calling the function again after the detection has finished will start another scan.
 */

#include "IdDetection.h"

#include "hal/derivative.h"
#include "BoardAssignment.h"
#include "IdDetection.h"
#include "VitalSignsMonitor.h"
#include "TMCL.h"


// Detect IDs of attached boards - returns true when done
uint8_t IDDetection_detect(IdAssignmentTypeDef *ids)
{
	ids->ch1.id 			= ID_TMC4671;
	ids->ch1.state 			= ID_STATE_DONE;
	IdState.ch1.detectedBy 	= FOUND_BY_EEPROM;

	ids->ch2.id 			= ID_TMC6100_BOB;
	ids->ch2.state 			= ID_STATE_DONE;
	IdState.ch2.detectedBy 	= FOUND_BY_EEPROM;
	return true;
}

void IDDetection_initialScan(IdAssignmentTypeDef *ids)
{
	while(!IDDetection_detect(ids))
	{
		vitalsignsmonitor_checkVitalSigns();
		tmcl_process();
	}
}
