/*
 * API_uart.h
 *
 *  Created on: 20 sep 2022
 *      Author: marti
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* P5_1 - Inclusión de tipos de datos de tamaño fijo */
#include <stdint.h>
#include <stdbool.h>

typedef bool bool_t;

bool_t uartInit(void);
void uartsendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif /* API_INC_API_UART_H_ */
