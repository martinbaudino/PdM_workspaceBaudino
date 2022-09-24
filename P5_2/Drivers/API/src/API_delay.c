/*
 * API_delay.c
 *
 *  Created on: 6 sep. 2022
 *      Author: msb
 */
#include "API_delay.h"

// P3_1: Mueve las definiciones de las funciones de termporización a su propio módulo

void delayInit(delay_t *delay, tick_t duration) {
	// Comprueba delay válido antes de configurarlo
	if (delay != NULL && duration != 0 && duration < DELAY_MAX) {
		delay->duration = duration;
		delay->running = false;
		delay->startTime = 0;
	} else {
		// Si se intenta configurar un delay muy grande genera error
		/* Turn LED2 on */
		BSP_LED_On(LED2);
		while (1) {
		}

	}

}

bool_t delayRead(delay_t *delay) {
	bool_t delay_state;

	// Previene lectura de delays inválidos por punteros no inicializados
	if (delay != NULL) {
		if (delay->running == false) {
			// Primera llamada, empieza a contar el tiempo
			delay->startTime = HAL_GetTick();
			delay->running = true;
			delay_state = false;
		} else {
			// Llamadas posteriores a la primera
			// Haciendo la resta se tiene en cuenta el desborde del uwTick
			if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
				delay->running = false;
				delay_state = true;
			} else
				delay_state = false;
		}
	} else {
		delay_state = false;
	}
	return delay_state;
}

void delayWrite(delay_t *delay, tick_t duration) {
	// Comprueba delay válido antes de modificarlo
	if (delay != NULL && duration != 0 && duration < DELAY_MAX) {
		delay->duration = duration;
	} else {

	}
}
