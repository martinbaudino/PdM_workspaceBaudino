/*
 * API_delay.h
 *
 *  Created on: 6 sep. 2022
 *      Author: msb
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

// P3_1: Mueve las definiciones de las funciones de termporización a su propio módulo

/* Includes ------------------------------------------------------------------*/
/* P2_1 - Inclusión de tipos de datos de tamaño fijo */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

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
/* P2_1 - Tiempo máximo posible para delay en 10 segggundos */
#define DELAY_MAX 10000U

/* Exported functions ------------------------------------------------------- */
/* P2_1 - Declaraciones de funciones para retardos no bloqueantes */

void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);

#endif /* API_INC_API_DELAY_H_ */
