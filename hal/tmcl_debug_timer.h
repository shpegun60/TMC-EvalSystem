/*
 * tmcl_debug_timer.h
 *
 *  Created on: Sep 30, 2023
 *      Author: admin
 */

#ifndef _TMCL_DEBUG_TIMER_H_
#define _TMCL_DEBUG_TIMER_H_

#include "main.h"


typedef void (*timer_overflow_t)(TIM_HandleTypeDef* const htim);

void setOverflowCallback(timer_overflow_t foo);
int debugTimerIsInitialized(void);
void setDebugPeriodMin(uint16_t period_min);
void setFrequencyMin(float freq_min);
uint16_t getDebugPeriod();
void setDebugFrequency(float freq);

void debugTimerStart(void);


#endif /* _TMCL_DEBUG_TIMER_H_ */
