/*
 * stm32_meta.h
 *
 *  Created on: May 13, 2024
 *      Author: Shpegun60
 */

#ifndef APP_DRV_IO_H_
#define APP_DRV_IO_H_

#include "main.h"

#ifdef HAL_GPIO_MODULE_ENABLED
// TMC_IO -----------------------------------------------------------
typedef struct TMC_GPIO
{
	//**********************
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
} IOPinTypeDef;


typedef GPIO_PinState IO_States;


#endif /* HAL_GPIO_MODULE_ENABLED */

#endif /* APP_DRV_IO_H_ */
