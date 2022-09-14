/*
 * API_debounce.h
 *
 *  Created on: 13 sep 2022
 *      Author: marti
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

/* P2_1 - Inclusión de tipos de datos de tamaño fijo */
#include <stdint.h>
#include <stdbool.h>


/* Exported types ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

/**
 * @fn void debounceFSM_init(void)
 * @brief
 *
 */
void debounceFSM_init(void);	// debe cargar el estado inicial

/**
 * @fn void debounceFSM_update(void)
 * @brief debe leer las entradas, resolver la lógica de transición de estados
 * 		  y actualizar las salidas
 *
 */
void debounceFSM_update(void);


/**
 * @fn bool_t readKey()
 * @brief La función readKey debe leer una variable interna del módulo y
 * devolver true o false si la tecla fue presionada.  Si devuelve true,
 * debe resetear (poner en false) el estado de la variable.
 *
 * @return
 */
bool readKey(void);



#endif /* API_INC_API_DEBOUNCE_H_ */
