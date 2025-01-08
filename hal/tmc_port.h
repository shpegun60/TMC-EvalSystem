/*
 * tmc_led.h
 *
 *  Created on: Jan 7, 2025
 *      Author: admin
 */

#ifndef TMC_EVALSYSTEM_HAL_TMC_PORT_H_
#define TMC_EVALSYSTEM_HAL_TMC_PORT_H_

#include "main.h"

// leds ----------------------------------------------------------------------
#define TMC_LED_TOGGLE() HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)
#define TMC_LED_ERROR_ON() HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
#define TMC_LED_ERROR_OFF() HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)

// enable --------------------------------------------------------------------
#define MOTION_CTRL_ENABLE() HAL_GPIO_WritePin(CTRL_EN_GPIO_Port, CTRL_EN_Pin, GPIO_PIN_SET)
#define MOTION_CTRL_DISABLE() HAL_GPIO_WritePin(CTRL_EN_GPIO_Port, CTRL_EN_Pin, GPIO_PIN_RESET)

// SPI - CTRL ---------------------------------------------------------------------
extern SPI_HandleTypeDef hspi1;

#define CTRL_CS_LOW() HAL_GPIO_WritePin(CS_CTRL_GPIO_Port, CS_CTRL_Pin, GPIO_PIN_RESET)
#define CTRL_CS_HIGH() HAL_GPIO_WritePin(CS_CTRL_GPIO_Port, CS_CTRL_Pin, GPIO_PIN_SET)
#define CTRL_SPI_READ_WRITE(tx_ptr, rx_ptr, size) HAL_SPI_TransmitReceive(&hspi1, (tx_ptr), (rx_ptr), (size), 1000)

// SPI - DRIVER -------------------------------------------------------------------
#define DRIVER_CS_LOW() HAL_GPIO_WritePin(CS_DRV_GPIO_Port, CS_DRV_Pin, GPIO_PIN_RESET)
#define DRIVER_CS_HIGH() HAL_GPIO_WritePin(CS_DRV_GPIO_Port, CS_DRV_Pin, GPIO_PIN_SET)
#define DRIVER_SPI_READ_WRITE(tx_ptr, rx_ptr, size) HAL_SPI_TransmitReceive(&hspi1, (tx_ptr), (rx_ptr), (size), 1000)

#endif /* TMC_EVALSYSTEM_HAL_TMC_PORT_H_ */
