/*
 * API_debounce.c
 *
 *  Created on: 13 sep 2022
 *      Author: marti
 */
#include "API_debounce.h"
#include "API_delay.h"

/**
 * @fn void buttonPressed(void)
 * @brief debe togglear el LED1
 *
 */
static void buttonPressed(void);

/**
 * @fn void buttonReleased(void)
 * @brief debe togglear el LED3
 *
 */
static void buttonReleased(void);

/* Private define ------------------------------------------------------------*/
#define TIME_DEBOUNCE  40U
typedef enum {
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;
#define BOT_ON		0U
#define BOT_OFF		1U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* P4_2 - Variable de retardo no bloqueante */
static delay_t bounce_delay;

// P4_2 - Variable de estado (global)
static debounceState_t curr_state;

static bool_t pending_pressed;

void debounceFSM_init(void){
	curr_state = BUTTON_UP;
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED3);
	delayInit(&bounce_delay, TIME_DEBOUNCE);
	pending_pressed = false;
}


void debounceFSM_update(void) {
	switch (curr_state) {
	case BUTTON_UP:
		if (BSP_PB_GetState(BUTTON_USER) == BOT_OFF) {
			delayRead(&bounce_delay);
			curr_state = BUTTON_FALLING;
		}
		break;

	case BUTTON_FALLING:
		if (delayRead(&bounce_delay)) {
			if (BSP_PB_GetState(BUTTON_USER) == BOT_OFF) {
				curr_state = BUTTON_DOWN;
				buttonPressed();
			} else {
				curr_state = BUTTON_UP;
			}
		}
		break;

	case BUTTON_DOWN:
		if (BSP_PB_GetState(BUTTON_USER) == BOT_ON) {
			delayRead(&bounce_delay);
			curr_state = BUTTON_RAISING;
		}
		break;

	case BUTTON_RAISING:
		if (delayRead(&bounce_delay)) {
			if (BSP_PB_GetState(BUTTON_USER) == BOT_ON) {
				curr_state = BUTTON_UP;
				buttonReleased();
			} else {
				curr_state = BUTTON_DOWN;
			}
		}
		break;

	default:
		//Si algo modificó la variable estadoActual
		// a un estado no válido llevo la MEF a un
		// lugar seguro, por ejemplo, la reinicio:
		//controlDeErrores();
		debounceFSM_init();
		break;
	}
}


static void buttonPressed(void){
	BSP_LED_Toggle(LED1);
	pending_pressed = true;
}


static void buttonReleased(void){
	BSP_LED_Toggle(LED3);
}

bool readKey(void){
	bool_t pending_aux;

	pending_aux = pending_pressed;
	pending_pressed = false;

	return pending_aux;
}

