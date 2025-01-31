/**
 ******************************************************************************
 * @file    UART/UART_Printf/Inc/main.h
 * @author  MCD Application Team
 * @brief   Header for main.c module
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* P2_1 - Inclusión de tipos de datos de tamaño fijo */
#include <stdint.h>
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
/* P2_1 - Tipos de datos para retardos no bloqueantes */
typedef uint32_t tick_t;
typedef bool bool_t;
typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

/* Exported constants --------------------------------------------------------*/
/* P2_1_1 - Tiempo máximo posible para delay en 10 segggundos */
#define DELAY_MAX 10000U

/* User can use this section to tailor USARTx/UARTx instance used and associated
 resources */
/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* P2_1 - Declaraciones de funciones para retardos no bloqueantes */

/**
 * @fn void delayInit(delay_t*, tick_t)
 * @brief	P2_1_1 - Configura un retardo no bloqueante de hasta DELAY_MAX
 * 			milisegundos pero NO empieza a contar el tiempo
 *
 * @param delay	puntero a estructura de temporizador
 * @param duration	retardo deseado
 */
void delayInit(delay_t *delay, tick_t duration);

/**
 * @fn bool_t delayRead(delay_t*)
 * @brief P2_1_2 - Lee el estado de un delay no bloqueante. En la primera llamada
 * 		  empieza a correr el tiempo. Cuando se cumple el tiempo detiene el
 * 		  contador.
 *
 * @param delay	puntero a estructura de temporizador
 * @return	Devuelve "false" si no transcurrió el tiempo del delay, y
 * 			"true" cuando se pasó la cuenta.
 */
bool_t delayRead(delay_t *delay);

/**
 * @fn void delayWrite(delay_t*, tick_t)
 * @brief 	P2_1_3 - Cambia el tiempo de duración de un delay no bloqueante ya
 * 			configurado y que puede estar corriendo.
 *
 * @param delay	puntero a estructura de temporizador
 * @param duration	retardo deseado
 */
void delayWrite(delay_t *delay, tick_t duration);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
