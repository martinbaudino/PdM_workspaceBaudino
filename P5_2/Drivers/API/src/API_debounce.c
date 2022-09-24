/*
 * API_debounce.c
 *
 *  Created on: 13 sep 2022
 *      Author: marti
 */
#include "API_debounce.h"
#include "API_delay.h" // Módulo autocontenido incluye sus dependendcias


/* Private typedef -----------------------------------------------------------*/

/**
 * @enum debounceState_t
 * @brief Enumeración de estados para la MEF de código anti-rebotes
 *
 */
typedef enum {
	BUTTON_UP, /**< BUTTON_UP El pulsador está liberado */
	BUTTON_FALLING,/**< BUTTON_FALLING Está ocurriendo un flanco descendente */
	BUTTON_DOWN, /**< BUTTON_DOWN Está ocurriendo un flanco ascendente */
	BUTTON_RAISING, /**< BUTTON_RAISING El botón está presionado */
} debounceState_t;

/* Private define ------------------------------------------------------------*/

#define TIME_DEBOUNCE  40U	// Retardo de 40ms para filtro anti-rebotes
#define BOT_ON		0U
#define BOT_OFF		1U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* P4_2 - Retardo no bloqueante, acceso privado dentro del archivo */
static delay_t bounce_delay;

/* P4_2 - Estado de a MEF, acceso privado dentro del archivo */
static debounceState_t curr_state;

/* P4_2 - Pulsación efectiva detectada, acceso privado dentro del arhivo */
static bool_t pending_pressed;


/* Private function prototypes -----------------------------------------------*/

static void buttonPressed(void);	// Calificador static impude acceso a
static void buttonReleased(void);	// estas funciones fuera del archivo


/* Function definitions ------------------------------------------------------*/

/**
 * @fn void debounceFSM_init(void)
 * @brief Inicializa la MEF
 *
 * Configura todos los parámetros necesarios para que la MEF comience en un
 * estado definido, con el botón libre, los LEDs apagados y el temporizador
 * configurado pero parado.
 */
void debounceFSM_init(void){
	curr_state = BUTTON_UP;
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED3);
	delayInit(&bounce_delay, TIME_DEBOUNCE);
	pending_pressed = false;
}

/**
 * @fn void debounceFSM_update(void)
 * @brief Ejecuta la MEF anti-rebotes
 *
 * Realiza lectura del Pin conectado al pulsador y actualiza el estado
 * correspondiente, detectando si las transiciones son rebotes o acciones
 * efectivas sobre el pulsador.
 */
void debounceFSM_update(void) {

	switch (curr_state) {
	case BUTTON_UP:
		if (BSP_PB_GetState(BUTTON_USER) == BOT_OFF) {
			delayRead(&bounce_delay);	// Si detecta flanco descendente cambia
			curr_state = BUTTON_FALLING;// el estado e inicia el retardo
		}
		break;

	case BUTTON_FALLING:
		if (delayRead(&bounce_delay)) {		// Si transcurrido el tiempo sigue
			if (BSP_PB_GetState(BUTTON_USER) == BOT_OFF) {
				curr_state = BUTTON_DOWN;	//  BAJO, cambia el estado y ejecuta
				buttonPressed();		 	//  acción correspondiente
			} else {
				curr_state = BUTTON_UP;		// Si no, vuelve al estado anterior
			}
		}
		break;

	case BUTTON_DOWN:
		if (BSP_PB_GetState(BUTTON_USER) == BOT_ON) {
			delayRead(&bounce_delay);	// Si detecta flanco ascendente cambia
			curr_state = BUTTON_RAISING;// el estado e inicia el retardo
		}
		break;

	case BUTTON_RAISING:
		if (delayRead(&bounce_delay)) {		// Si transcurrido el tiempo sigue
			if (BSP_PB_GetState(BUTTON_USER) == BOT_ON) {
				curr_state = BUTTON_UP;		// ALTO, cambia el estado y ejecuta
				buttonReleased();			//  acción correspondiente
			} else {
				curr_state = BUTTON_DOWN;	// Si no, vuelve al estado anterior
			}
		}
		break;

	default:
		/**
		 * Si algo modificó la variable curr_state a un estado no válido lleva
		 * la MEF a un lugar seguro, en este caso la inicializa nuevamente
		 */
		debounceFSM_init();
		break;
	}
}


/**
 * @fn void buttonPressed(void)
 * @brief Acción correspondiente a pulsado efectivo del pulsador
 *
 */
static void buttonPressed(void){
	BSP_LED_Toggle(LED1);
	pending_pressed = true;
}


/**
 * @fn void buttonReleased(void)
 * @brief Acción correspondiente a liberación efectiva del pulsador
 *
 */
static void buttonReleased(void){
	BSP_LED_Toggle(LED3);
}

/**
 * @fn bool_t readKey()
 * @brief La función readKey debe leer una variable interna del módulo y
 * devolver true o false si la tecla fue presionada.  Si devuelve true,
 * debe resetear (poner en false) el estado de la variable.
 *
 * @return
 */
bool readKey(void){
	bool_t pending_aux;

	pending_aux = pending_pressed;
	pending_pressed = false;

	return pending_aux;
}

