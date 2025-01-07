/*
 * tmc_led.h
 *
 *  Created on: Jan 7, 2025
 *      Author: admin
 */

#ifndef TMC_EVALSYSTEM_HAL_TMC_PORT_H_
#define TMC_EVALSYSTEM_HAL_TMC_PORT_H_

#include "main.h"

#define TMC_LED_TOGGLE() HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)
#define TMC_LED_ERROR_ON() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define TMC_LED_ERROR_OFF() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)


#define MOTION_CTRL_ENABLE() HAL_GPIO_WritePin(CTRL_EN_GPIO_Port, CTRL_EN_Pin, GPIO_PIN_SET)
#define MOTION_CTRL_DISABLE() HAL_GPIO_WritePin(CTRL_EN_GPIO_Port, CTRL_EN_Pin, GPIO_PIN_RESET)


#endif /* TMC_EVALSYSTEM_HAL_TMC_PORT_H_ */
