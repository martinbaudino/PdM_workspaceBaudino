/*
 * API_delay.c
 *
 *  Created on: 6 sep. 2022
 *      Author: msb
 */
#include "API_delay.h"

// P3_1: Mueve las definiciones de las funciones de termporización a su propio módulo

/**
 * @fn void delayInit(delay_t*, tick_t)
 * @brief	P2_1_1 - Inicializa retardo no bloqueante
 *
 * Configura un retardo no bloqueante de hasta DELAY_MAX milisegundos pero
 * NO empieza a contar el tiempo
 *
 * @param delay	puntero a estructura de temporizador
 * @param duration	retardo deseado
 */
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

/**
 * @fn bool_t delayRead(delay_t*)
 * @brief P2_1_2 - Lee el estado de un delay no bloqueante.
 *
 * En la primera llamada empieza a correr el tiempo. Cuando se cumple el
 * tiempo detiene el contador.
 *
 * @param delay	puntero a estructura de temporizador
 * @return	Devuelve "false" si no transcurrió el tiempo del delay, y
 * 			"true" cuando se pasó la cuenta.
 */
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

/**
 * @fn void delayWrite(delay_t*, tick_t)
 * @brief 	P2_1_3 - Cambia el tiempo de duración de un delay no bloqueante
 *
 * El delay debe estar inicializado pero estar corriendo o detenido.
 *
 * @param delay	puntero a estructura de temporizador
 * @param duration	retardo deseado
 */
void delayWrite(delay_t *delay, tick_t duration) {
	// Comprueba delay válido antes de modificarlo
	if (delay != NULL && duration != 0 && duration < DELAY_MAX) {
		delay->duration = duration;
	} else {

	}
}
