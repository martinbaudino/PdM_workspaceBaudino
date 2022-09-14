/*
 * API_debounce.h
 *
 *  Created on: 13 sep 2022
 *      Author: marti
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

/* P4_2 - Inclusión de tipos de datos de tamaño fijo */
#include <stdint.h>
#include <stdbool.h>


/* Exported types ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

void debounceFSM_init(void);	// debe cargar el estado inicial
void debounceFSM_update(void);
bool readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
